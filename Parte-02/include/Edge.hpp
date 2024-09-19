#ifndef GRAFO_BASICO_EDGE_HPP
#define GRAFO_BASICO_EDGE_HPP

#include "Node.hpp"
#include "defines.hpp"

struct Node;
struct Edge
{
    // atributos da aresta
    Edge *_next_edge;
    Node *_target;
};

#endif // GRAFO_BASICO_EDGE_HPP