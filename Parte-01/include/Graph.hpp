#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"

class Graph
{
public:
    // construtor e destrutor
    Graph(ifstream &instance, bool directed, bool weight_edges, bool weight_nodes);
    Graph();
    ~Graph();

    // métodos básicos
    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight);
    void add_edge(size_t node_id_1, size_t node_id_2, float weight);
    void print_graph(ofstream &output_file);
    void print_graph();
    int conected(size_t node_id_1, size_t node_id_2);

    // métodos de funcionalidades
    void dfs_transitive(size_t vertex, vector<bool> &visited, bool direct);
    bool dfs_call(size_t vertex, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list);
    void dfs_recursive(Node *node, vector<bool> &visited, vector<pair<size_t, size_t>> &return_edges, map<size_t, vector<size_t>> &adj_list, int parent_id);
    void dfs_articulation(size_t i, vector<bool> &visited, vector<int> &disc_time, vector<int> &low_time, vector<size_t> &parent, vector<bool> &art_point, int &time);
    void dijkstra(size_t source, vector<float> &distance, vector<int> &parents, vector<size_t> &node_at_index);
    void floyd(size_t vertex_1, vector<vector<float>> &distance, vector<vector<int>> &parents, vector<size_t> &node_at_index);
    void floyd(vector<vector<float>> &distance);
    void prim(size_t *vertices, size_t size, vector<size_t> &parent, vector<float> &key, vector<bool> &mst_set, size_t start_node);
    void kruskal(vector<pair<float, pair<size_t, size_t>>> &edges, size_t *vertices, size_t size, function<size_t(size_t, size_t *)> &find_ds, vector<pair<float, pair<size_t, size_t>>> &tree_edges);
    void compute_graph_properties(float &radius, float &diameter, vector<size_t> &center, vector<size_t> &periphery);

    // métodos de acesso público
    size_t get_num_nodes();
    size_t get_num_edges();
    bool get_directed();
    bool get_weighted_nodes();
    bool get_weighted_edges();
    Node *find_node(size_t node_id);
    Edge *find_edge(size_t node_id_1, size_t node_id_2);
    int is_connected(size_t *vertices, size_t size);
    bool is_connected_graph();

private:
    // atributos do grafo
    size_t _number_of_nodes;
    size_t _number_of_edges;
    bool _directed;
    bool _weighted_edges;
    bool _weighted_nodes;
    Node *_first;
    Node *_last;

    // métodos de acesso privado
    void read_graph(ifstream &instance);
    bool negative_cycle(size_t vertex);
    void dfs(Node *node, vector<bool> &visited, size_t *vertices, size_t size);
    void dfs(Node *node, vector<bool> &visited);
};

#endif // GRAPH_HPP