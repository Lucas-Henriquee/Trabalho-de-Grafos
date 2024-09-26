#ifndef GRAPH_PARTITIONING_HPP
#define GRAPH_PARTITIONING_HPP

#include "Graph.hpp"
#include "defines.hpp"

void select_algorithm(Graph *g, char algorithm, string filename, string file_exit);
void greedy_partitioning(Graph *g);
void randomized_greedy_partitioning(Graph *g, float alpha);
void reactive_randomized_greedy_partitioning(Graph *g, vector<float> alphas);
void print_execution_time(clock_t start, clock_t end);
void print_greedy(string file_exit);

#endif // GRAPH_PARTITIONING_HPP