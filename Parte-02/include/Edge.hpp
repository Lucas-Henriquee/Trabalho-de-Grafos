#ifndef GRAFO_BASICO_EDGE_HPP
#define GRAFO_BASICO_EDGE_HPP

#include "defines.hpp"

struct Edge
{
    // atributos da aresta
    Edge *_next_edge;
    size_t _target_id;
};

#endif // GRAFO_BASICO_EDGE_HPP