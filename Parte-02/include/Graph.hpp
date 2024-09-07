#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"

class Graph
{
public:
    // construtor e destrutor
    Graph(ifstream &instance);
    Graph();
    ~Graph();

    // métodos básicos
    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight);
    void add_edge(size_t node_id_1, size_t node_id_2);
    void print_graph(ofstream &output_file);
    void print_graph();
    int conected(size_t node_id_1, size_t node_id_2);

    // métodos de acesso público
    size_t get_num_nodes();
    size_t get_num_edges();
    Node *find_node(size_t node_id);
    Edge *find_edge(size_t node_id_1, size_t node_id_2);
    int is_connected(size_t *vertices, size_t size);
    bool is_connected_graph();

private:
    // atributos do grafo
    size_t _number_of_nodes;
    size_t _number_of_edges;
    Node *_first;
    Node *_last;

    // métodos de acesso privado
    void read_graph(ifstream &instance);
    bool negative_cycle(size_t vertex);
    void dfs(Node *node, vector<bool> &visited, size_t *vertices, size_t size);
    void dfs(Node *node, vector<bool> &visited);
};

#endif // GRAPH_HPP