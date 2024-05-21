#include "../include/Graph.hpp"
#include <sstream>
using namespace std;

Graph::Graph(std::ifstream &instance, bool directed, bool weight_edges, bool weight_nodes)
{
    _directed = directed;
    _weighted_edges = weight_edges;
    _weighted_nodes = weight_nodes;

    _number_of_edges = 0;
    _number_of_nodes = 0;

    _first = NULL;
    _last = NULL;

    string line;

    while (getline(instance, line))
    {
        if (line.empty())
            continue;

        istringstream iss(line);

        size_t node_1, node_2;
        float node_1_weight = 0.0, node_2_weight = 0.0, edge_weight = 0.0;

        if (_weighted_nodes && _weighted_edges)
            iss >> node_1 >> node_1_weight >> node_2 >> node_2_weight >> edge_weight;
        else if (_weighted_nodes)
            iss >> node_1 >> node_1_weight >> node_2 >> node_2_weight;
        else if (_weighted_edges)
            iss >> node_1 >> node_2 >> edge_weight;
        else
            iss >> node_1 >> node_2;

        add_node(node_1, node_1_weight);
        add_node(node_2, node_2_weight);

        add_edge(node_1, node_2, edge_weight);
    }
}

Graph::Graph()
{
}

Graph::~Graph()
{
    Node *aux_node_1 = _first;

    while (aux_node_1 != NULL)
    {
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

void Graph::remove_node(size_t node_position)
{
    Node *aux_node = find_node(node_position);

    if (!aux_node)
    {
        cout << "  Erro: O Nó não foi encontrado no grafo." << endl;
        return;
    }
    // retirar o nó da(s) aresta(s) do grafo
    // atualizar a lista encadeada
    // liberar memória
}

void Graph::remove_edge(size_t node_position_1, size_t node_position_2)
{
    Node *aux_node_1 = find_node(node_position_1);
    Node *aux_node_2 = find_node(node_position_2);

    if (!aux_node_1 || !aux_node_2)
    {
        cout << "  Erro: Ao menos um dos Nós não foi encontrado." << endl;
        return;
    }

    Edge *aux_edge_1 = aux_node_1->_first_edge;
    Edge *aux_edge_2 = NULL;

    while (aux_edge_1 != NULL)
    {
        if (aux_edge_1->_target_id == node_position_2)
        {

            if (aux_edge_2 != NULL)
                aux_edge_2->_next_edge == aux_edge_1->_next_edge;
            else
                aux_node_1->_first_edge = aux_edge_1->_next_edge;

            delete aux_edge_1;
            aux_node_1->_number_of_edges--;
            break;
        }
        aux_edge_2 = aux_edge_1;
        aux_edge_1 = aux_edge_1->_next_edge;
    }
}

void Graph::add_node(size_t node_id, float weight)
{
    if (find_node(node_id))
        return;

    Node *aux = new Node;
    aux->_number_of_edges = 0;
    aux->_id = node_id;
    aux->_weight = weight;
    if (_last == NULL)
    {
        _first = aux;
        _last = aux;
    }
    else
    {
        _last->_next_node = aux;
        aux->_previous_node = _last;
        _last = aux;
    }
    _number_of_nodes++;
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
    Node *search_node_1 = find_node(node_id_1);
    Node *search_node_2 = find_node(node_id_2);

    if (!search_node_1 || !search_node_2)
        return;

    Edge *new_edge_1 = new Edge;
    new_edge_1->_target_id = node_id_2;
    new_edge_1->_weight = weight;
    new_edge_1->_next_edge = NULL;
    search_node_1->_number_of_edges = +1;
    if (search_node_1->_first_edge != NULL)
    {
        Edge *aux_edge = search_node_1->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge->_next_edge)
        {
        }
        aux_edge->_next_edge = new_edge_1;
    }
    else
        search_node_1->_first_edge = new_edge_1;
    if (!_directed)
    {
        Edge *new_edge_2 = new Edge;
        new_edge_2->_target_id = node_id_1;
        new_edge_2->_weight = weight;
        new_edge_2->_next_edge = NULL;
        search_node_2->_number_of_edges = +1;
        if (search_node_2->_first_edge != NULL)
        {
            Edge *aux_edge = search_node_2->_first_edge;
            for (; aux_edge->_next_edge != NULL; aux_edge->_next_edge)
            {
            }
            aux_edge->_next_edge = new_edge_2;
        }
        else
            search_node_2->_first_edge = new_edge_2;
    }
}

void Graph::print_graph()
{
    for (Node *node = _first; node != NULL; node = node->_next_node)
    {
        cout << node->_id;
        for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
            cout << " -> " << edge->_target_id;
    }
    cout << endl;
}

void Graph::print_graph(std::ofstream &output_file)
{
    output_file << "  \n\t\tImprimindo Grafo " << endl;

    output_file << "  \tDados do Grafo: \n  Número de Nós: " << _number_of_nodes << "  Número de Arestas: " << _number_of_edges << endl;

    if (_first == NULL)
        return;

    for (Node *node = _first; node != NULL; node = node->_next_node)
    {
        output_file << node->_id;
        for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
            output_file << " -> " << edge->_target_id;
    }

    output_file << endl;

    output_file << "\n\n\n\tFuncionalidades solicitadas para a impressão:  " << endl;
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    if (!aux_node_1 || !aux_node_2)
        return 0;

    for (Edge *aux_edge = aux_node_1->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        if (aux_edge->_target_id == node_id_2)
            return 1;

    return 0;
}

Node *Graph::find_node(size_t node_id)
{
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        if (aux_node->_id == node_id)
            return aux_node;
    return NULL;
}
