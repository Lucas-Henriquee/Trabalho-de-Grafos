#include "../include/Graph.hpp"

Graph::Graph(std::ifstream &instance){

}

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::remove_node(size_t node_position)
{
}

void Graph::remove_edge(size_t node_position_1, size_t node_position_2)
{
}

void Graph::add_node(size_t node_id, float weight)
{
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
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
    Node *search_node_1 = NULL;
    Node *search_node_2 = NULL;
    Node *aux_node = _first;
    for (size_t i = 0; i < _number_of_nodes; i++)
    {
        if (aux_node->_id == node_id_1)
        {
            search_node_1 = aux_node;
        }
        if (aux_node->_id == node_id_2)
        {
            search_node_2 = aux_node;
        }
        if (search_node_1 != NULL && search_node_2 != NULL)
        {
            break;
        }
    }
    if (search_node_1 == NULL || search_node_2 == NULL)
    {
        return;
    }
    if (search_node_1->_first_edge != NULL)
    {
        Edge *aux_edge = search_node_1->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge->_next_edge){}
        Edge *new_edge = new Edge;
        new_edge->_target_id = node_id_2;
        new_edge->_weight = weight;
        new_edge->_next_edge = NULL;
        aux_edge->_next_edge = new_edge;
    }
    else{
        Edge *new_edge = new Edge;
        new_edge->_target_id = node_id_2;
        new_edge->_weight = weight;
        new_edge->_next_edge = NULL;
        search_node_1->_first_edge = new_edge
    }
    if (_directed && search_node_2->_first_edge != NULL)
    {
        Edge *aux_edge = search_node_2->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge->_next_edge){}
        Edge *new_edge = new Edge;
        new_edge->_target_id = node_id_1;
        new_edge->_weight = weight;
        new_edge->_next_edge = NULL;
        aux_edge->_next_edge = new_edge;
    }
    else{
        Edge *new_edge = new Edge;
        new_edge->_target_id = node_id_1;
        new_edge->_weight = weight;
        new_edge->_next_edge = NULL;
        search_node_2->_first_edge = new_edge
    }
}

void Graph::print_graph()
{
}

void Graph::print_graph(std::ofstream &output_file)
{
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    return 0;
}
