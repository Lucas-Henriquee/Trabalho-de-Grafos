#include "../include/Graph.hpp"
#include "../include/defines.hpp"

Graph::Graph(ifstream &instance)
{
    // Inicializa o número de arestas, nós e subgrafos.
    _number_of_edges = 0;
    _number_of_nodes = 0;
    _number_of_subgraphs = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;

    // Chamando a função para ler o grafo.
    read_graph(instance);
}

Graph::Graph()
{
    // Inicializa o número de arestas, nós e subgrafos.
    _number_of_edges = 0;
    _number_of_nodes = 0;
    _number_of_subgraphs = 0;

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
    // Inicializando a string para leitura do arquivo.
    string line;

    // Lendo o número de subgrafos.
    while (getline(instance, line))
    {
        // Procurando a linha que contém o número de subgrafos.
        if (line.find("param p") != string::npos)
        {
            // Lendo o número de subgrafos.
            istringstream iss(line);
            string discard;
            iss >> discard >> discard >> discard >> _number_of_subgraphs;
            break;
        }
    }

    // Lendo os pesos dos vértices
    while (getline(instance, line))
    {
        // Procurando a linha que contém os pesos dos vértices.
        if (line.find("param w") != string::npos)
        {
            // Lendo os pesos dos vértices.
            while (getline(instance, line))
            {
                // Se encontrar a próxima seção, terminar a leitura dos pesos
                if (line.find(";") != string::npos)
                    break;

                // Inicializando o fluxo de leitura da linha.
                istringstream iss(line);
                size_t node;
                float weight;

                // Lendo o vértice e seu peso e atualizando o peso do vértice.
                while (iss >> node >> weight)
                    add_node(node, weight);
            }
            break;
        }
    }

    // Lendo as arestas do grafo.
    while (getline(instance, line))
    {
        // Procurando a linha que contém as arestas do grafo.
        if (line.find("set E") != string::npos)
        {
            while (getline(instance, line))
            {
                // Inicializando o fluxo de leitura da linha.
                istringstream iss(line);
                char discard;
                size_t node_1, node_2;

                // Lendo pares de vértices que formam uma aresta
                while (iss >> discard >> node_1 >> discard >> node_2 >> discard)
                    add_edge(node_1, node_2);

                // Se encontrar a próxima seção, terminar a leitura das arestas
                if (line.find(";") != string::npos)
                    break;
            }
            break;
        }
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
    Node **conected_nodes = new Node*[aux_node->_number_of_edges];

    // Armazenando os nós conectados ao nó a ser removido.
    int i = 0;
    for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
    {
        conected_nodes[i] = aux_edge->_target;
        i++;
    }

    // Removendo as arestas do nó a ser removido.
    for (size_t i = 0; i < aux_node->_number_of_edges; i++)
        remove_edge(node_id, conected_nodes[i]->_id);

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
        if (aux_edge_1->_target->_id == node_id_2)
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
    _number_of_nodes++;
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

void Graph::add_edge(size_t node_id_1, size_t node_id_2)
{
    // Procurando se os nós já existem.
    Node *search_node_1 = find_node(node_id_1);
    Node *search_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!search_node_1 || !search_node_2)
        return;

    // Criando uma nova aresta.
    Edge *new_edge_1 = new Edge;
    new_edge_1->_target = search_node_2;
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

    // Criando uma nova aresta.
    Edge *new_edge_2 = new Edge;
    new_edge_2->_target = search_node_1;
    new_edge_2->_next_edge = NULL;
    // Atualizando o número de arestas.
    search_node_2->_number_of_edges = search_node_2->_number_of_edges + 1;
    // Verificando se o nó possui arestas.
    if (search_node_2->_first_edge != NULL)
    {
        // Adicionando a aresta ao nó.
        Edge *aux_edge = search_node_2->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge = aux_edge->_next_edge)
            ;
        aux_edge->_next_edge = new_edge_2;
    }
    // Caso o nó não possua arestas.
    else
        search_node_2->_first_edge = new_edge_2;

    // Atualizando o número de arestas.
    _number_of_edges = _number_of_edges + 1;
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
        if (aux_edge->_target->_id == node_id_2)
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
        if (aux_edge->_target->_id == node_id_2)
            return aux_edge;

    // Caso a aresta não exista.
    return NULL;
}

size_t Graph::get_num_edges()
{
    // Retornando o número de arestas.
    return _number_of_edges;
}

size_t Graph::get_num_subgraphs()
{
    // Retornando o número de subgrafos.
    return _number_of_subgraphs;
}

Node *Graph::get_first_node()
{
    // Retornando o primeiro nó do grafo.
    return _first;
}

float Graph::get_node_weight(size_t node_id)
{
    // Encontrando o nó.
    Node *aux_node = find_node(node_id);

    // Verificando se o nó foi encontrado.
    if (!aux_node)
    {
        cerr << "Node << " << node_id << " >> not found." << endl;
        return -1;
    }

    // Retornando o peso do nó.
    return aux_node->_weight;
}

void Graph::dfs(Node *node, vector<bool> &visited)
{
    // Marcando o nó como visitado.
    visited[node->_id - 1] = true;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = find_node(edge->_target->_id);

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

void Graph::print_graph()
{
    // Inicializando o nó auxiliar para percorrer o grafo.
    Node *aux_node_1 = _first;

    // Percorrendo todos os nós do grafo.
    while (aux_node_1 != NULL)
    {
        // Imprimindo o nó.
        cout << "Node: " << aux_node_1->_id << " Weight: " << aux_node_1->_weight << endl;

        // Percorrendo todas as arestas do nó.
        Edge *aux_edge_1 = aux_node_1->_first_edge;
        while (aux_edge_1 != NULL)
        {
            // Imprimindo a aresta.
            cout << "Edge: " << aux_node_1->_id << " -> " << aux_edge_1->_target->_id << endl;

            // Atualizando a aresta auxiliar.
            aux_edge_1 = aux_edge_1->_next_edge;
        }

        // Atualizando o nó auxiliar.
        aux_node_1 = aux_node_1->_next_node;
    }
}