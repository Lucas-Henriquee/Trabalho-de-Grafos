#include "../include/Graph.hpp"
#include "../include/defines.hpp"

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
    // Inicializa as variáveis.
    _directed = false;
    _weighted_edges = false;
    _weighted_nodes = false;

    // Inicializa o número de arestas e nós.
    _number_of_edges = 0;
    _number_of_nodes = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;
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
        float node_1_weight = 1.0, node_2_weight = 1.0, edge_weight = 1.0;

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
        return;

    // Verificando se a remoção do nó deixará o grafo desconexo.
    for (size_t i = 0; i < _number_of_nodes; ++i)
        if (i != node_id && !(conected(node_id, i) || conected(i, node_id)))
            return;

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
        return;

    // Verificando se a remoção da aresta deixará o grafo desconexo.
    if (!conected(node_id_1, node_id_2) && !conected(node_id_2, node_id_1))
        return;

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
    aux->_next_node = NULL;
    aux->_first_edge = NULL;

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
            ;
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
    // Implementação da função de impressão do grafo no menu.

    int i = 0;

    while (i != -1)
    {
        system("clear||cls");
        cout << "\n\t\t\t Grafo\n\n\n";

        cout << "  Dados do Grafo:" << endl;
        cout << "  Número de Nós: " << _number_of_nodes << endl;
        cout << "  Número de Arestas: " << _number_of_edges << endl;
        cout << "  Tipo do Grafo: " << (_directed ? "Direcionado" : "Não Direcionado") << "\n\n\n";

        cout << "\n\n";

        // Imprimindo o grafo.
        for (Node *node = _first; node != NULL; node = node->_next_node)
        {
            cout << "\t\t\t" << node->_id;
            for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
                cout << " -> " << edge->_target_id;
            cout << endl;
        }

        cout << "\n\n  Digite -1 para voltar ao menu: ";
        cin >> i;
    }
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

Edge *Graph::find_edge(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser encontrada.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
        return NULL;

    // Verificando se a aresta existe.
    for (Edge *aux_edge = aux_node_1->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        if (aux_edge->_target_id == node_id_2)
            return aux_edge;

    // Caso a aresta não exista.
    return NULL;
}

size_t Graph::get_num_edges()
{
    // Retornando o número de arestas.
    return _number_of_edges;
}

bool Graph::dfs_call(size_t vertex, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list)
{
    // Inicializando o vetor de visitados.
    vector<bool> visited(_number_of_nodes, false);

    // Encontrando o nó inicial.
    Node *start_node = find_node(vertex);

    // Verificando se o nó foi encontrado.
    if (start_node != NULL)
    {
        // Chamando a função recursiva e retornando verdadeiro.
        dfs_recursive(start_node, visited, return_edges, adj_list, -1);
        return true;
    }

    // Caso o nó não seja encontrado.
    return false;
}

void Graph::dfs_recursive(Node *node, vector<bool> &visited, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list, int parent_id)
{
    // Marca o nó como visitado.
    visited[node->_id] = true;

    // Vetor para armazenar os vizinhos do nó.
    vector<size_t> neighbors;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = find_node(edge->_target_id);

        // Adicionando o nó destino ao vetor de vizinhos.
        neighbors.push_back(edge->_target_id);

        // Verificando se o nó destino ainda não foi visitado e chamando a função recursivamente.
        if (!visited[edge->_target_id])
            dfs_recursive(target_node, visited, return_edges, adj_list, node->_id);

        // Verificando se a aresta é de retorno.
        else if (edge->_target_id != static_cast<size_t>(parent_id))
        {
            // Verificando se a aresta já foi adicionada.
            if (find(return_edges.begin(), return_edges.end(), make_pair(edge->_target_id, node->_id)) == return_edges.end())
                return_edges.emplace_back(node->_id, edge->_target_id);
        }

        // Verificando se o grafo é não direcionado.
        if (!_directed)
        {
            // Verificando se o nó destino ainda não foi visitado.
            if (find(adj_list[target_node->_id].begin(), adj_list[target_node->_id].end(), node->_id) == adj_list[target_node->_id].end())
                adj_list[target_node->_id].push_back(node->_id);
        }
    }

    // Adicionando os vizinhos do nó ao mapa.
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

        // Marcando no vetor que o nó foi visitado, mas sem marcar o nó inicial.
        if (aux_node_1->_id != vertex)
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

void Graph::dfs_articulation(size_t i, vector<bool> &visited, vector<int> &disc_time, vector<int> &low_time, vector<size_t> &parent, vector<bool> &art_point, int &time)
{
    // Inicializando o nó como visitado.
    visited[i] = true;

    // Inicializando o tempo de descoberta e o tempo de baixo.
    disc_time[i] = low_time[i] = ++time;

    // Inicializando o número de filhos do nó.
    int children = 0;

    // Encontrando o nó atual.
    Node *aux_node = find_node(i + 1);

    // Loop para percorrer todas as arestas do nó.
    for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        size_t v = aux_edge->_target_id - 1; // Ajuste do índice do nó.

        // Verificando se o nó destino ainda não foi visitado.
        if (!visited[v])
        {
            // Incrementando o número de filhos do nó.
            children++;

            // Atualizando o pai do nó destino.
            parent[v] = i;

            // Chamando a função recursivamente para o nó destino.
            dfs_articulation(v, visited, disc_time, low_time, parent, art_point, time);

            // Atualizando o tempo de baixo do nó atual.
            low_time[i] = min(low_time[i], low_time[v]);

            // Verificando se o nó atual é a raiz da árvore e possui mais de um filho.
            if (parent[i] == static_cast<size_t>(-1) && children > 1)
                art_point[i] = true;

            // Verificando se o nó atual não é a raiz da árvore e o tempo de baixo do nó destino é maior ou igual ao tempo de descoberta do nó atual.
            if (parent[i] != static_cast<size_t>(-1) && low_time[v] >= disc_time[i])
                art_point[i] = true;
        }
        // Verificando se o nó destino já foi visitado e se ele não é o pai do nó atual.
        else if (v != parent[i])
            low_time[i] = min(low_time[i], disc_time[v]);
    }
}

void Graph::dijkstra(size_t source, vector<float> &distance, vector<int> &parents, vector<size_t> &node_at_index)
{
    // Inicializando as variáveis.
    int n = _number_of_nodes;
    int p = 0;

    // Inicializando as distâncias e os pais.
    distance.assign(n, FLT_MAX);
    parents.assign(n, -1);

    // Inicializando os nós visitados.
    vector<bool> visited(n, false);
    int unvisited_nodes = n;

    // Inicializando vetor para mapear a posição do nó.
    node_at_index.assign(n, -1);
    node_at_index[p] = source;

    // Inicializando o nó de origem com 0.
    distance[p] = 0;

    // Loop para encontrar o menor caminho.
    for (int i = 0; i < unvisited_nodes;)
    {
        // Encontrando o vértice com a menor distância.
        int v = -1;
        for (int j = 0; j < n; j++)
            if ((!visited[j]) && (v == -1 || distance[j] < distance[v]))
                v = j;

        // Se não houver vértice com a menor distância.
        if (distance[v] == FLT_MAX)
            break;

        // Marcando o vértice como visitado.
        visited[v] = true;
        unvisited_nodes--;

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
                if (visited[position])
                {
                    visited[position] = false;
                    unvisited_nodes++;
                }
            }
        }
    }
}

void Graph::floyd(vector<vector<float>> &distance, vector<vector<int>> &parents, vector<size_t> &node_at_index)
{
    // Inicializando as variáveis.
    size_t n = _number_of_nodes;
    size_t v = 0;

    // Inicializando as matrizes de distância e de pais.
    distance.assign(n, vector<float>(n, FLT_MAX));
    parents.assign(n, vector<int>(n, -1));

    // Inicializando o vetor de mapeamento de nós.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
    {
        node_at_index[v] = aux_node->_id;
        distance[v][v] = 0;
        parents[v][v] = v;
        v++;
    }

    // Atualizando a variável de controle.
    v = 0;

    // Preenchendo a matriz de distâncias e de pais.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
    {
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            size_t u = find(node_at_index.begin(), node_at_index.end(), aux_edge->_target_id) - node_at_index.begin();
            distance[v][u] = aux_edge->_weight;
            parents[v][u] = v;
        }

        v++;
    }
    // Aplicando o algoritmo de Floyd-Warshall para encontrar as distâncias mínimas.
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
    // Inicializando a matriz de distâncias com o algoritmo de Floyd-Warshall.
    for (size_t k = 0; k < _number_of_nodes; ++k)
        for (size_t i = 0; i < _number_of_nodes; ++i)
            for (size_t j = 0; j < _number_of_nodes; ++j)
                if (distance[i][k] < FLT_MAX && distance[k][j] < FLT_MAX)
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
}

void Graph::compute_graph_properties(float &radius, float &diameter, vector<size_t> &center, vector<size_t> &periphery)
{
    // Inicializando a matriz de distâncias.
    vector<vector<float>> dist(_number_of_nodes, vector<float>(_number_of_nodes, FLT_MAX));

    // Preenchendo a matriz de distâncias com base nas arestas do grafo.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
    {
        // Encontrando o nó atual e inicializando a distância dele para ele mesmo.
        size_t id = aux_node->_id;
        dist[id - 1][id - 1] = 0;

        // Preenchendo a distância do nó atual para os nós adjacentes.
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            // Encontrando o nó adjacente e preenchendo a distância.
            size_t target_id = aux_edge->_target_id;

            // Se o grafo for direcionado, preenchendo a distância do nó atual para o nó adjacente.
            dist[id - 1][target_id - 1] = aux_edge->_weight;

            // Se o grafo não for direcionado, preenchendo a distância do nó adjacente para o nó atual.
            if (!_directed)
                dist[target_id - 1][id - 1] = aux_edge->_weight;
        }
    }

    // Aplicando o algoritmo de Floyd-Warshall para encontrar as distâncias mínimas.
    floyd(dist);

    // Inicializando o raio e o diâmetro.
    diameter = 0;
    vector<float> eccentricity(_number_of_nodes, 0);

    // Encontrando a excentricidade de cada nó e o diâmetro.
    for (size_t i = 0; i < _number_of_nodes; ++i)
    {
        // Encontrando a distância máxima do nó i para os outros nós.
        float max_dist = 0;

        // Se a distância for infinita, o nó é desconexo.
        for (size_t j = 0; j < _number_of_nodes; ++j)
            if (dist[i][j] < FLT_MAX)
                max_dist = max(max_dist, dist[i][j]);

        // Se o nó é desconexo, ignoramos na excentricidade.
        if (max_dist > 0)
        {
            eccentricity[i] = max_dist;
            diameter = max(diameter, max_dist);
        }
    }

    // Encontrando o raio.
    radius = *min_element(eccentricity.begin(), eccentricity.end());

    // Encontrando o centro e a periferia.
    for (size_t i = 0; i < _number_of_nodes; ++i)
    {
        if (eccentricity[i] == radius)
            center.push_back(i + 1);
        if (eccentricity[i] == diameter)
            periphery.push_back(i + 1);
    }
}

bool Graph::negative_cycle(size_t vertex)
{
    // Inicializando o vetor de arestas.
    vector<pair<float, pair<size_t, size_t>>> edges;

    // Preenchendo o vetor de arestas com base nas arestas do grafo.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
            edges.push_back({aux_edge->_weight, {aux_node->_id, aux_edge->_target_id}});

    // Inicializando o vetor de distâncias.
    vector<float> dist(_number_of_nodes, FLT_MAX);

    // Inicializando a distância do nó inicial como 0.
    dist[vertex - 1] = 0;

    // Aplicando o algoritmo de Bellman-Ford para encontrar ciclos negativos.
    for (size_t i = 0; i < _number_of_nodes; i++)
        for (size_t j = 0; j < edges.size(); j++)
        {
            // Encontrando os nós da aresta.
            size_t u = edges[j].second.first - 1;
            size_t v = edges[j].second.second - 1;

            // Encontrando o peso da aresta.
            float weight = edges[j].first;

            // Atualizando a distância se a nova distância for menor.
            if (dist[u] != FLT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }

    // Verificando se há ciclo negativo.
    for (size_t i = 0; i < edges.size(); i++)
    {
        // Encontrando os nós da aresta.
        size_t u = edges[i].second.first - 1;
        size_t v = edges[i].second.second - 1;

        // Encontrando o peso da aresta.
        float weight = edges[i].first;

        // Verificando se a distância pode ser atualizada.
        if (dist[u] != FLT_MAX && dist[u] + weight < dist[v])
            return true;
    }

    // Caso não haja ciclo negativo.
    return false;
}

bool Graph::is_connected(size_t *vertices, size_t size)
{
    // Verificando se o grafo está vazio.
    if (_first == NULL)
        return false;

    // Inicializando o vetor de visitados.
    vector<bool> visited(size, false);

    // Encontrando o primeiro nó do grafo.
    Node *start_node = find_node(vertices[0]);

    // Chamando a função de busca em profundidade.
    dfs(start_node, visited, vertices, size);

    // Verificando se todos os nós foram visitados.
    return find(visited.begin(), visited.end(), false) == visited.end();
}

void Graph::dfs(Node *node, vector<bool> &visited, size_t *vertices, size_t size)
{
    // Marcando o nó como visitado.
    visited[find(vertices, vertices + size, node->_id) - vertices] = true;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = find_node(edge->_target_id);
        if (find(vertices, vertices + size, edge->_target_id) == vertices + size)
            continue;

        // Verificando se o nó destino ainda não foi visitado.
        if (!visited[edge->_target_id])
            dfs(target_node, visited);
    }
}

void Graph::dfs(Node *node, vector<bool> &visited)
{
    // Marcando o nó como visitado.
    visited[node->_id - 1] = true;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = find_node(edge->_target_id);

        // Verificando se o nó destino ainda não foi visitado.
        if (!visited[target_node->_id - 1])
            dfs(target_node, visited);
    }
}

bool Graph::is_connected_graph()
{
    // Verificando se o grafo está vazio.
    if (_first == NULL)
        return false;

    // Inicializando o vetor de nós visitados.
    vector<bool> visited(_number_of_nodes, false);

    // Iniciando a DFS a partir do primeiro nó do grafo.
    Node *start_node = _first;
    dfs(start_node, visited);

    // Verificando se todos os nós foram visitados (grafo conexo).
    return find(visited.begin(), visited.end(), false) == visited.end();
}

vector<tuple<size_t, size_t, float>> Graph::primMST(size_t* node_id, size_t node_id_size)
{
    if (node_id_size == 0) return;

    // Inicialização dos vetores
    vector<tuple<size_t, size_t, float>> prim_results(node_id_size,{0,0,0}); // Vetor de resultados
    vector<size_t> minWeight(node_id_size, INF_F); // Peso mínimo de aresta para cada vértice
    vector<int> parent(node_id_size, -1); // Vértice pai para a árvore
    vector<bool> inMST(node_id_size, false); // Para marcar vértices incluídos na MST

    // Começar com o primeiro vértice
    size_t startVertex = node_id[0];
    minWeight[startVertex] = 0;
    parent[startVertex] = -1;

    for (size_t i = 0; i < node_id_size - 1; ++i) 
    {
        // Encontrar o vértice com o menor peso de aresta que ainda não está na MST
        size_t min_node = -1;
        size_t minWeightValue = INF_F;
        for (size_t j = 0; j < node_id_size; ++j)
        {
            if (!inMST[node_id[j]] && minWeight[node_id[j]] < minWeightValue) 
            {
                min_node = node_id[j];
                minWeightValue = minWeight[node_id[j]];
            }
        }

        // Adicionar o vértice encontrado à MST
        inMST[min_node] = true;

        // Atualizar os pesos e pais dos vértices adjacentes
        Node* aux_node=this->find_node(min_node);
        Edge* aux_edge=aux_node->_first_edge;
            while (aux_edge!=NULL)
            {
                size_t aux_edge_target_index=-1;
                size_t aux_edge_target = aux_edge->_target_id;
                for (size_t i = 0; i < node_id_size; ++i)
                {
                    if(node_id[i]==aux_edge_target)
                    aux_edge_target_index=i;
                }
                


                if (aux_edge_target_index!=-1 && !inMST[aux_edge_target_index] && aux_edge->_weight < minWeight[aux_edge_target])
                {
                    minWeight[aux_edge_target_index] = aux_edge->_weight;
                    parent[aux_edge_target_index] = min_node;
                }
                aux_edge=aux_edge->_next_edge;
            }
    }

    //Salvar resultados na ordem: {id do vértice, pai, peso mínimo}
    for (size_t i = 0; i < node_id_size; ++i)
    {
        prim_results[i]={node_id[i], parent[i], minWeight[i]};
    }
    return prim_results;
}

void Graph::kruskal(){}