#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"

using namespace std;

class Graph
{
public:
    /*Assinatura dos métodos básicos para o funcionamento da classe*/

    Graph(ifstream &instance, bool directed, bool weight_edges, bool weight_nodes);
    Graph();
    ~Graph();

    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight = 0);
    void add_edge(size_t node_id_1, size_t node_id_2, float weight = 0);
    void print_graph(ofstream &output_file);
    void print_graph();
    int conected(size_t node_id_1, size_t node_id_2);

    void dfs(Graph *g, size_t vertex,  vector<pair<size_t, size_t>> &return_edges, string &tree);
    void dfs_transitive(size_t vertex, vector<Node *> &visited, bool direct);
    void dfs_articulation();
    void dijkstra(size_t source, vector<float> &distance, vector<int> &parents, vector<size_t> &node_at_index);

    size_t get_num_nodes();
    Node *get_first_node();

private:
    size_t _number_of_nodes;
    size_t _number_of_edges;
    bool _directed;
    bool _weighted_edges;
    bool _weighted_nodes;
    Node *_first;
    Node *_last;

    Node *find_node(size_t node_id);
};

#endif // GRAPH_HPP
