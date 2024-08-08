#ifndef GRAPH_OPERATIONS_HPP
#define GRAPH_OPERATIONS_HPP

#include "Graph.hpp"
#include "defines.hpp"

void menu(Graph *g, string file_exit);
bool validate_graph(Graph *g, int i);
void transitive_direct(Graph *g, size_t vertex);
void transitive_indirect(Graph *g, size_t vertex);
void dijkstra_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2);
void floyd_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2);
void prim_minimum_generating_tree(Graph *g, size_t *vertices, size_t size);
void kruskal_minimum_generating_tree(Graph *g, size_t *vertices, size_t size);
void deep_walking(Graph *g, size_t vertex);
void properties_graph(Graph *g);
void articulation_vertices(Graph *g);
void save_exit(Graph *g, string file);
void print_start();
void sleep_for_seconds(int seconds);

#endif // GRAPH_OPERATIONS_HPP