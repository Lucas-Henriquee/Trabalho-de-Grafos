#ifndef SUBGRAPH_HPP
#define SUBGRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"

class SubGraph
{
public:
    // construtor e destrutor
    SubGraph();
    ~SubGraph();

    // métodos básicos
    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight);
    void add_edge(size_t node_id_1, size_t node_id_2);
    int conected(size_t node_id_1, size_t node_id_2);

    // métodos de acesso público
    size_t get_num_nodes();
    size_t get_num_edges();
    float get_min_weight();
    float get_max_weight();
    float get_gap();
    Node *get_first_node();
    Node *get_last_node();
    Node *find_node(size_t node_id);
    Edge *find_edge(size_t node_id_1, size_t node_id_2);
    bool is_connected_subgraph();
    float get_node_weight(size_t node_id);
    void print_graph();

private:
    // atributos do grafo
    size_t _number_of_nodes;
    size_t _number_of_edges;
    float min_weight;
    float max_weight;
    Node *_first;
    Node *_last;

    // métodos de acesso privadox
    void dfs(Node *node, vector<bool> &visited, vector<size_t> &node_at_index);
    void update_weight();
};

#endif // SUBGRAPH_HPP