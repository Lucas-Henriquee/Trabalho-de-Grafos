#include "../include/Graph.hpp"

Graph::Graph(std::ifstream& instance)
{
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
    Node* aux = new Node;
    aux->_number_of_edges = 0;
    aux->_id = node_id;
    aux->_weight = weight;
    if(_last == NULL){
        _first = aux;
        _last = aux;
    }
    else{
        _last->_next_node = aux;
        aux->_previous_node = _last;
        _last = aux;
    }
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
}

void Graph::print_graph()
{
}

void Graph::print_graph(std::ofstream& output_file)
{
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    return 0;
}
