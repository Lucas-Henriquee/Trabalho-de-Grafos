#ifndef GRAPH_PARTITIONING_HPP
#define GRAPH_PARTITIONING_HPP

#include "Graph.hpp"
#include "defines.hpp"

void select_algorithm(Graph *g, char algorithm);
void greedy_partitioning(Graph *g);
void randomized_greedy_partitioning(Graph *g, float alpha);
void reactive_randomized_greedy_partitioning(Graph *g, vector<float> alphas);
void calculete_gap(Graph *sub_g);
bool partition_is_valid(Graph *sub_g);

#endif // GRAPH_PARTITIONING_HPP