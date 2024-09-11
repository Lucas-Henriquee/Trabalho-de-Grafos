#include "../include/Graph.hpp"
#include "../include/GraphPartitioning.hpp"
#include "../include/defines.hpp"

void select_algorithm(Graph *g, char algorithm)
{
    switch (algorithm)
    {
    case '0':
        greedy_partitioning(g);
        break;
    case '1':
        randomized_greedy_partitioning(g);
        break;
    case '2':
        reactive_randomized_greedy_partitioning(g);
        break;
    default:
        cout << "Algoritmo inválido" << endl;
        break;
    }
}

void greedy_partitioning(Graph *g)
{
}

void randomized_greedy_partitioning(Graph *g)
{
}

void reactive_randomized_greedy_partitioning(Graph *g)
{
}

void calculete_gap(Graph *sub_g)
{
}

bool partition_is_valid(Graph *sub_g)
{
}