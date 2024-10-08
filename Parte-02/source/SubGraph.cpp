
#include "../include/SubGraph.hpp"
#include "../include/defines.hpp"

SubGraph::SubGraph()
{
    // Inicializa o número de arestas, nós e subgrafos.
    _number_of_edges = 0;
    _number_of_nodes = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;
}

SubGraph::~SubGraph()
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

void SubGraph::remove_node(size_t node_id)
{
    vector<size_t> node_at_index;
    for (Node* aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        node_at_index.push_back(aux_node->_id);
    

    // Encontrando o nó a ser removido.
    Node *aux_node = find_node(node_id);

    // Verificando se o nó foi encontrado.
    if (!aux_node)
        return;

    // Inicializando o vetor de nós conectados.
    size_t *conected_nodes = new size_t[aux_node->_number_of_edges];

    // Armazenando os nós conectados ao nó a ser removido.
    int i = 0;
    for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
    {
        conected_nodes[i] = aux_edge->_target->_id;
        i++;
    }

    // Removendo as arestas do nó a ser removido.
    for (size_t i = 0; i < aux_node->_number_of_edges; i++)
    {
        remove_edge(node_id, conected_nodes[i]);
        remove_edge(conected_nodes[i], node_id);
    }        

    // Atualizando a lista de nós.
    if(aux_node != _first && aux_node != _last)
    {
        aux_node->_next_node->_previous_node = aux_node->_previous_node;
        aux_node->_previous_node->_next_node = aux_node->_next_node;
    }
    if(aux_node == _first && aux_node == _last)
    {
        _first = NULL;
        _last = NULL;
    }
    if(aux_node == _first)
    {
        _first = aux_node->_next_node;
        aux_node->_next_node->_previous_node = NULL;
    }
    if(aux_node == _last)
    {
        _last = aux_node->_previous_node;
        aux_node->_previous_node->_next_node = NULL;
    }

    // Atualizando o número de nós.
    _number_of_nodes--;

    // Deletando o nó.
    update_weight();
    delete aux_node;
    delete[] conected_nodes;
}

void SubGraph::update_weight(){
    if(_first == NULL){
        min_weight = 0;
        max_weight = 0;
        return;
    }
    min_weight = _first->_weight;
    max_weight = _first->_weight;
    for(Node* aux_node = _first;aux_node != NULL; aux_node = aux_node->_next_node){
        if(aux_node->_weight < min_weight)
            min_weight = aux_node->_weight;
        if(aux_node->_weight > max_weight)
            max_weight = aux_node->_weight;
    }
}

void SubGraph::remove_edge(size_t node_id_1, size_t node_id_2)
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

void SubGraph::add_node(size_t node_id, float weight)
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
        min_weight = weight;
        max_weight = weight;
    }

    // Caso contrário.
    else
    {
        _last->_next_node = aux;
        aux->_previous_node = _last;
        _last = aux;
        if(min_weight > weight)
            min_weight = weight;
        else if(max_weight < weight)
            max_weight = weight;
    }
    _number_of_nodes++;
}

void SubGraph::add_edge(size_t node_id_1, size_t node_id_2)
{
    // Procurando se os nós já existem.
    Node *search_node_1 = find_node(node_id_1);
    Node *search_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!search_node_1 || !search_node_2)
        return;

    // Criando uma nova aresta.
    Edge *new_edge_1 = new Edge;
    new_edge_1->_target = find_node(node_id_2);
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
    new_edge_2->_target = find_node(node_id_1);
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

int SubGraph::conected(size_t node_id_1, size_t node_id_2)
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

Node *SubGraph::find_node(size_t node_id)
{
    // Procurando o nó.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        if (aux_node->_id == node_id)
            return aux_node;

    // Caso o nó não seja encontrado.
    return NULL;
}

size_t SubGraph::get_num_nodes()
{
    // Retornando o número de nós.
    return _number_of_nodes;
}

float SubGraph::get_min_weight()
{
    // Retornando o peso mínimo.
    return min_weight;
}

float SubGraph::get_max_weight()
{
    // Retornando o peso máximo.
    return max_weight;
}

float SubGraph::get_gap()
{
    // Retornando a diferença entre o peso máximo e o peso mínimo.
    return get_max_weight() - get_min_weight();
}

Edge *SubGraph::find_edge(size_t node_id_1, size_t node_id_2)
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

size_t SubGraph::get_num_edges()
{
    // Retornando o número de arestas.
    return _number_of_edges;
}
Node *SubGraph::get_first_node()
{
    // Retornando o primeiro nó do grafo.
    return _first;
}

Node *SubGraph::get_last_node()
{
    // Retornando o último nó do grafo.
    return _last;
}

float SubGraph::get_node_weight(size_t node_id)
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

void SubGraph::dfs(Node *node, vector<bool> &visited, vector<size_t> &node_at_index)
{
    // Marcando o nó como visitado.
    visited[find(node_at_index.begin(), node_at_index.end(), node->_id) - node_at_index.begin()] = true;

    // Loop para percorrer todas as arestas do nó.
    for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
    {
        // Encontrando o nó destino da aresta.
        Node *target_node = edge->_target;

        // Verificando se o nó destino ainda não foi visitado.
        if (!visited[find(node_at_index.begin(), node_at_index.end(), target_node->_id) - node_at_index.begin()])
            dfs(target_node, visited, node_at_index);
    }
}

bool SubGraph::is_connected_subgraph()
{
    // Verificando se o grafo está vazio.
    if (_first == NULL)
        return false;
    vector<size_t> node_at_index;
    for(Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        node_at_index.push_back(aux_node->_id);

    // Inicializando o vetor de nós visitados.
    vector<bool> visited(_number_of_nodes, false);

    // Iniciando a DFS a partir do primeiro nó do grafo.
    Node *start_node = _first;
    dfs(start_node, visited, node_at_index);

    // Verificando se todos os nós foram visitados (grafo conexo).
    return find(visited.begin(), visited.end(), false) == visited.end();
}