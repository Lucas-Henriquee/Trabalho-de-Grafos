#include "../include/Graph.hpp"
#include "../include/defines.hpp"
#include "../include/Graph.hpp"

#define INF_F numeric_limits<float>::infinity()

using namespace std;

Graph::Graph(ifstream &instance, bool directed, bool weight_edges, bool weight_nodes)
{
    // Inicializa as variáveis.
    _directed = directed;
    _weighted_edges = weight_edges;
    _weighted_nodes = weight_nodes;

    // Inicializa o número de arestas e nós.
    _number_of_edges = 0;
    _number_of_nodes = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;

    // Chamando a função para ler o grafo.
    read_graph(instance);
}

Graph::Graph()
{
    // TODO: Implementar o construtor padrão.
}

Graph::~Graph()
{
    // Criando o nó auxiliar para percorrer o grafo.
    Node *aux_node_1 = _first;

    // Percorrendo todos os nós do grafo.
    while (aux_node_1 != NULL)
    {
        // Realizando processo de remoção das arestas.
        Edge *aux_edge_1 = aux_node_1->_first_edge;
        while (aux_edge_1 != NULL)
        {
            Edge *aux_edge_2 = aux_edge_1->_next_edge;
            delete aux_edge_1;
            aux_edge_1 = aux_edge_2;
        }
        Node *aux_node_2 = aux_node_1->_next_node;
        delete aux_node_1;
        aux_node_1 = aux_node_2;
    }
}

void Graph::read_graph(ifstream &instance)
{
    // String para armazenar a linha do arquivo.
    string line;

    // Lendo primeira linha.
    getline(instance, line);
    istringstream iss(line);
    iss >> _number_of_nodes;
    for (size_t i = 1; i <= _number_of_nodes; i++)
        add_node(i, 0);

    // Inicializando leitura do arquivo.
    while (getline(instance, line))
    {
        // Se houver linha vazia durante a leitura.
        if (line.empty())
            continue;

        // Inicializa a leitura da linha.
        istringstream iss(line);

        // Variáveis para armazenar os valores da linha.
        size_t node_1, node_2;
        float node_1_weight = 0.0, node_2_weight = 0.0, edge_weight = 0.0;

        // Realizando a leitura dos valores.
        if (_weighted_nodes && _weighted_edges)
            iss >> node_1 >> node_1_weight >> node_2 >> node_2_weight >> edge_weight;
        else if (_weighted_nodes)
            iss >> node_1 >> node_1_weight >> node_2 >> node_2_weight;
        else if (_weighted_edges)
            iss >> node_1 >> node_2 >> edge_weight;
        else
            iss >> node_1 >> node_2;

        // Adicionando os nós e as arestas ao grafo.
        add_edge(node_1, node_2, edge_weight);
    }
}

void Graph::remove_node(size_t node_id)
{
    // Encontrando o nó a ser removido.
    Node *aux_node = find_node(node_id);

    // Verificando se o nó foi encontrado.
    if (!aux_node)
    {
        cout << "  Erro: O Nó não foi encontrado no grafo." << endl;
        return;
    }

    //! VERIFICAR SE É NECESSÁRIO INCLUIR ESTA VERIFICAÇÃO.
    // Verificando se a remoção do nó deixará o grafo desconexo.
    for (size_t i = 0; i < _number_of_nodes; ++i)
        if (i != node_id && !(conected(node_id, i) || conected(i, node_id)))
        {
            cout << "  Erro: A remoção do nó " << node_id << " deixaria o grafo desconexo." << endl;
            return;
        }

    // Inicializando o vetor de nós conectados.
    size_t *conected_nodes = new size_t[aux_node->_number_of_edges];

    // Armazenando os nós conectados ao nó a ser removido.
    int i = 0;
    for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
    {
        conected_nodes[i] = aux_edge->_target_id;
        i++;
    }

    // Removendo as arestas do nó a ser removido.
    for (size_t i = 0; i < aux_node->_number_of_edges; i++)
        remove_edge(node_id, conected_nodes[i]);

    // Atualizando a lista de nós.
    aux_node->_next_node = aux_node->_previous_node;
    aux_node->_previous_node = aux_node->_next_node;

    // Atualizando o número de nós.
    _number_of_nodes--;

    // Deletando o nó.
    delete aux_node;
    delete[] conected_nodes;
}

void Graph::remove_edge(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser removida.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
    {
        cout << "  Erro: Ao menos um dos Nós não foi encontrado." << endl;
        return;
    }

    //! VERIFICAR SE É NECESSÁRIO INCLUIR ESTA VERIFICAÇÃO.
    // Verificando se a remoção da aresta deixará o grafo desconexo.
    if (!conected(node_id_1, node_id_2) && !conected(node_id_2, node_id_1))
    {
        cout << "  Erro: A remoção da aresta (" << node_id_1 << ", " << node_id_2 << ") deixaria o grafo desconexo." << endl;
        return;
    }

    // Inicializando as arestas auxiliares.
    Edge *aux_edge_1 = aux_node_1->_first_edge;
    Edge *aux_edge_2 = NULL;

    // Procurando a aresta a ser removida.
    while (aux_edge_1 != NULL)
    {
        // Verificando se a aresta foi encontrada.
        if (aux_edge_1->_target_id == node_id_2)
        {
            // Atualizando a lista de arestas.
            if (aux_edge_2 != NULL)
                aux_edge_2->_next_edge = aux_edge_1->_next_edge;
            else
                aux_node_1->_first_edge = aux_edge_1->_next_edge;

            delete aux_edge_1;
            aux_node_1->_number_of_edges--;
            break;
        }

        // Atualizando as arestas auxiliares.
        aux_edge_2 = aux_edge_1;
        aux_edge_1 = aux_edge_1->_next_edge;
    }
}

void Graph::add_node(size_t node_id, float weight)
{
    // Verificando se o nó já existe.
    if (find_node(node_id) != NULL)
        return;

    // Criando um novo nó.
    Node *aux = new Node;
    aux->_number_of_edges = 0;
    aux->_id = node_id;
    aux->_weight = weight;

    // Verificando se o grafo está vazio.
    if (_last == NULL)
    {
        _first = aux;
        _last = aux;
    }

    // Caso contrário.
    else
    {
        _last->_next_node = aux;
        aux->_previous_node = _last;
        _last = aux;
    }
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
    // Procurando se os nós já existem.
    Node *search_node_1 = find_node(node_id_1);
    Node *search_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!search_node_1 || !search_node_2)
        return;

    // Criando uma nova aresta.
    Edge *new_edge_1 = new Edge;
    new_edge_1->_target_id = node_id_2;
    new_edge_1->_weight = weight;
    new_edge_1->_next_edge = NULL;

    // Atualizando o número de arestas.
    search_node_1->_number_of_edges = search_node_1->_number_of_edges + 1;

    // Verificando se o nó possui arestas.
    if (search_node_1->_first_edge != NULL)
    {
        // Adicionando a aresta ao nó.
        Edge *aux_edge = search_node_1->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
        }
        aux_edge->_next_edge = new_edge_1;
    }

    // Caso o nó não possua arestas.
    else
        search_node_1->_first_edge = new_edge_1;

    // Verificando se o grafo é direcionado.
    if (!_directed)
    {
        // Criando uma nova aresta.
        Edge *new_edge_2 = new Edge;
        new_edge_2->_target_id = node_id_1;
        new_edge_2->_weight = weight;
        new_edge_2->_next_edge = NULL;

        // Atualizando o número de arestas.
        search_node_2->_number_of_edges = search_node_2->_number_of_edges + 1;

        // Verificando se o nó possui arestas.
        if (search_node_2->_first_edge != NULL)
        {
            // Adicionando a aresta ao nó.
            Edge *aux_edge = search_node_2->_first_edge;
            for (; aux_edge->_next_edge != NULL; aux_edge = aux_edge->_next_edge)
            {
            }
            aux_edge->_next_edge = new_edge_2;
        }

        // Caso o nó não possua arestas.
        else
            search_node_2->_first_edge = new_edge_2;
    }

    // Atualizando o número de arestas.
    _number_of_edges = _number_of_edges + 1;
}

void Graph::print_graph()
{
    cout << "\n\n";

    // Imprimindo o grafo.
    for (Node *node = _first; node != NULL; node = node->_next_node)
    {
        cout << "\t\t\t" << node->_id;
        for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
            cout << " -> " << edge->_target_id;
        cout << endl;
    }

    cout << "\n\n Inicializando o Grafo...." << endl;
}

void Graph::print_graph(ofstream &output_file)
{
    // Armazena dados do grafo no buffer.
    output_file << "\n\t\t\t\tImprimindo Grafo\n\n\n";

    output_file << "  Dados do Grafo:" << endl;
    output_file << "  Número de Nós: " << _number_of_nodes << endl;
    output_file << "  Número de Arestas: " << _number_of_edges << endl;
    output_file << "  Tipo do Grafo: " << (_directed ? "Direcionado" : "Não Direcionado") << "\n\n\n";

    // Verifica se o grafo está vazio.
    if (_first == NULL)
    {
        output_file << "  O grafo está vazio." << endl;
        return;
    }

    // Itera sobre todos os nós do grafo
    for (Node *node = _first; node != NULL; node = node->_next_node)
    {
        // Imprime o nó atual
        output_file << "\t\t  " << node->_id;

        // Verifica se há arestas saindo do nó
        bool first_edge = true;
        for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
        {
            // Se não for a primeira aresta, adiciona a conexão
            if (first_edge)
            {
                output_file << " --(" << edge->_weight << ")--> " << edge->_target_id;
                first_edge = false;
            }
            else
            {
                output_file << " --(" << edge->_weight << ")--> " << edge->_target_id;
            }
        }
        // Quebra de linha após processar todas as arestas do nó atual
        output_file << endl;
    }

    output_file << "\n\n";
    output_file << "  Funcionalidades solicitadas do Grafo:\n";
    output_file << "  -------------------------------------------------------------\n\n";
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser encontrada.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
        return 0;

    // Verificando se a aresta existe.
    for (Edge *aux_edge = aux_node_1->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        if (aux_edge->_target_id == node_id_2)
            return 1;

    // Caso a aresta não exista.
    return 0;
}

Node *Graph::find_node(size_t node_id)
{
    // Procurando o nó.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        if (aux_node->_id == node_id)
            return aux_node;

    // Caso o nó não seja encontrado.
    return NULL;
}

size_t Graph::get_num_nodes()
{
    // Retornando o número de nós.
    return _number_of_nodes;
}

bool Graph::get_directed()
{
    // Retornando se o grafo é direcionado.
    return _directed;
}

bool Graph::get_weighted_nodes()
{
    // Retornando se o grafo possui nós ponderados.
    return _weighted_nodes;
}

bool Graph::get_weighted_edges()
{
    // Retornando se o grafo possui arestas ponderadas.
    return _weighted_edges;
}

bool Graph::dfs_call(size_t vertex, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list)
{
    // Vetor para armazenar os nós visitados.
    vector<bool> visited(_number_of_nodes, false);

    Node *start_node = find_node(vertex);

    // Verificando se o nó de início foi encontrado.
    if (start_node != NULL)
    {
        // Chamando a função dfs (Busca em Profundidade).
        dfs_recursive(start_node, visited, return_edges, adj_list);
        return true;
    }

    return false;
}
void Graph::dfs_recursive(Node *node, vector<bool> &visited, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list)
{
    // Marcando o nó como visitado.
    visited[node->_id] = true;

    // Vetor para armazenar os vizinhos do nó.
    vector<size_t> neighbors;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = find_node(edge->_target_id);

        // Adicionando o nó destino na lista de vizinhos.
        neighbors.push_back(edge->_target_id);

        // Verificando se o grafo é não-direcionado e adicionando a aresta em ambas as direções.
        if (!_directed)
            if (find(adj_list[target_node->_id].begin(), adj_list[target_node->_id].end(), node->_id) == adj_list[target_node->_id].end())
                adj_list[target_node->_id].push_back(node->_id);

        // Verificando se o nó destino ainda não foi visitado ou se o grafo é não-direcionado.
        if (!_directed || !visited[target_node->_id])
        {
            // Adicionando aresta de retorno, se ainda não foi adicionada e o grafo é não-direcionado.
            if (!_directed)
            {
                if (find(return_edges.begin(), return_edges.end(), make_pair(node->_id, target_node->_id)) == return_edges.end() && find(return_edges.begin(), return_edges.end(), make_pair(target_node->_id, node->_id)) == return_edges.end())
                    return_edges.emplace_back(node->_id, target_node->_id);
            }
            // Adicionando aresta de retorno, se ainda não foi adicionada e o grafo é direcionado.
            else
            {
                if (find(return_edges.begin(), return_edges.end(), make_pair(node->_id, target_node->_id)) == return_edges.end())
                    return_edges.emplace_back(node->_id, target_node->_id);
            }

            // Chamando a função recursivamente para o nó destino.
            if (!visited[target_node->_id])
                dfs_recursive(target_node, visited, return_edges, adj_list);
        }
    }

    // Adicionando a lista de vizinhos do nó atual.
    adj_list[node->_id] = move(neighbors);
}

void Graph::dfs_transitive(size_t vertex, vector<bool> &visited, bool direct)
{
    // Criando um nó inicial e chamando a função para encontrá-lo.
    Node *start_node = find_node(vertex);

    // Verificando se o nó existe.
    if (!start_node)
        return;

    // Inicializando uma pilha de ponteiros de nós.
    stack<Node *> stack_nodes;

    // Colocando o nó encontrado na pilha.
    stack_nodes.push(start_node);

    // O loop continua até que a pilha fique vazia.
    while (!stack_nodes.empty())
    {
        // O nó do topo da pilha é removido.
        Node *aux_node_1 = stack_nodes.top();
        stack_nodes.pop();

        // Verificando se o nó já foi visitado.
        if (visited[aux_node_1->_id])
            continue;

        // Marcando no vetor que o nó foi visitado.
        visited[aux_node_1->_id] = true;

        // Verificando se é um fecho transitivo direto.
        if (direct)
        {
            // Loop percorre todas as arestas que saem do nó aux_node_1.
            for (Edge *aux_edge_1 = aux_node_1->_first_edge; aux_edge_1 != NULL; aux_edge_1 = aux_edge_1->_next_edge)
            {
                // Encontrando o próximo nó (destino).
                Node *aux_node_2 = find_node(aux_edge_1->_target_id);

                // Verificando se o nó destino existe e se ele ainda não foi visitado.
                if (aux_node_2 && !visited[aux_node_2->_id])
                    stack_nodes.push(aux_node_2);
            }
        }

        // Caso não seja parte para o grafo reverso.
        else
        {
            // Loop para as arestas de entrada do nó aux_node_1.
            for (Node *aux_node_3 = _first; aux_node_3 != NULL; aux_node_3 = aux_node_3->_next_node)
            {
                // Percorrendo todas as arestas do nó atual que chegam ao nó aux_node_1.
                for (Edge *aux_edge_2 = aux_node_3->_first_edge; aux_edge_2 != NULL; aux_edge_2 = aux_edge_2->_next_edge)
                {
                    // Verificando se o destino da aresta é o nó atual (aux_node_1).
                    if (aux_edge_2->_target_id == aux_node_1->_id)
                    {
                        // Encontrando o próximo nó (origem da aresta).
                        Node *aux_node_2 = find_node(aux_node_3->_id);

                        // Verificando se o nó origem existe e se ele ainda não foi visitado.
                        if (aux_node_2 && !visited[aux_node_2->_id])
                            stack_nodes.push(aux_node_2);
                    }
                }
            }
        }
    }
}

void Graph::dfs_articulation()
{
    // TODO: Implementar a função de articulação.
}

void Graph::dijkstra(size_t source, vector<float> &distance, vector<int> &parents, vector<size_t> &node_at_index)
{
    // Inicializando as variáveis.
    int n = _number_of_nodes;
    int p = 0;

    // Inicializando as distâncias e os pais.
    distance.assign(n, INF_F);
    parents.assign(n, -1);

    // Inicializando os nós visitados.
    vector<bool> visited(n, false);

    // Inicializando vetor para mapear a posição do nó.
    node_at_index.assign(n, -1);
    node_at_index[p] = source;

    // Inicializando o nó de origem com 0.
    distance[p] = 0;

    // Loop para encontrar o menor caminho.
    for (int i = 0; i < n; i++)
    {
        // Encontrando o vértice com a menor distância.
        int v = -1;
        for (int j = 0; j < n; j++)
            if ((!visited[j]) && (v == -1 || distance[j] < distance[v]))
                v = j;

        // Se não houver vértice com a menor distância.
        if (distance[v] == INF_F)
            break;

        // Marcando o vértice como visitado.
        visited[v] = true;

        // Encontrando o nó no grafo.
        Node *aux_node = find_node(node_at_index[v]);

        // Iterando sobre todas as arestas do nó atual.
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            // Encontrando o nó destino e o peso da aresta.
            int target = aux_edge->_target_id;
            float weight = aux_edge->_weight;

            // Verificando se o nó destino já foi aramazenado no node_at_index.
            if (find(node_at_index.begin(), node_at_index.end(), target) == node_at_index.end())
            {
                p++;
                node_at_index[p] = target;
            }

            // Encontrando a posição do nó destino.
            int position = find(node_at_index.begin(), node_at_index.end(), target) - node_at_index.begin();

            // Atualizando a distância e o pai do nó se a nova distância for menor.
            if (distance[v] + weight < distance[position])
            {
                distance[position] = distance[v] + weight;
                parents[position] = v;
            }
        }
    }
}

void Graph::floyd(vector<vector<float>> &distance, vector<vector<int>> &parents, vector<size_t> &node_at_index)
{
    size_t n = _number_of_nodes;
    size_t v = 0;

    distance.assign(n, vector<float>(n, INF_F));
    parents.assign(n, vector<int>(n, -1));

    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
    {
        node_at_index[v] = aux_node->_id;
        distance[v][v] = 0;
        parents[v][v] = v;
        v++;
    }

    v = 0;

    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            size_t u = find(node_at_index.begin(), node_at_index.end(), aux_edge->_target_id) - node_at_index.begin();
            distance[v][u] = aux_edge->_weight;
            parents[v][u] = v;
        }
    v++;

    for (size_t k = 0; k < n; k++)
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
                if (distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    parents[i][j] = parents[k][j];
                }
}

void Graph::floyd(vector<vector<float>> &distance)
{
    for (size_t k = 0; k < _number_of_nodes; ++k)
        for (size_t i = 0; i < _number_of_nodes; ++i)
            for (size_t j = 0; j < _number_of_nodes; ++j)
                if (distance[i][k] < INF_F && distance[k][j] < INF_F)
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
}

void Graph::compute_graph_properties(float &radius, float &diameter, vector<size_t> &center, vector<size_t> &periphery)
{
    // Inicializando a matriz de distâncias
    vector<vector<float>> dist(_number_of_nodes, vector<float>(_number_of_nodes, INF_F));

    // Preenchendo a matriz de distâncias com base nas arestas do grafo
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
    {
        // Encontrando o nó atual e inicializando a distância dele para ele mesmo
        size_t id = aux_node->_id;
        dist[id - 1][id - 1] = 0;

        // Preenchendo a distância do nó atual para os nós adjacentes
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            // Encontrando o nó adjacente e preenchendo a distância
            size_t target_id = aux_edge->_target_id;
            dist[id - 1][target_id - 1] = aux_edge->_weight;

            // Se o grafo não for direcionado, preenchendo a distância do nó adjacente para o nó atual
            if (!_directed)
                dist[target_id - 1][id - 1] = aux_edge->_weight;
        }
    }

    // Aplicando o algoritmo de Floyd-Warshall para encontrar as distâncias mínimas
    floyd(dist);

    // Inicializando o raio e o diâmetro
    diameter = 0;
    vector<float> eccentricity(_number_of_nodes, 0);

    // Encontrando a excentricidade de cada nó e o diâmetro
    for (size_t i = 0; i < _number_of_nodes; ++i)
    {
        // Encontrando a distância máxima do nó i para os outros nós
        float max_dist = 0;
        for (size_t j = 0; j < _number_of_nodes; ++j)
            if (dist[i][j] < INF_F)
                max_dist = max(max_dist, dist[i][j]);

        // Atualizando a excentricidade e o diâmetro
        eccentricity[i] = max_dist;
        diameter = max(diameter, max_dist);
    }

    // Encontrando o raio
    radius = *min_element(eccentricity.begin(), eccentricity.end());

    // Encontrando o centro e a periferia
    for (size_t i = 0; i < _number_of_nodes; ++i)
    {
        if (eccentricity[i] == radius)
            center.push_back(i + 1);
        if (eccentricity[i] == diameter)
            periphery.push_back(i + 1);
    }
}