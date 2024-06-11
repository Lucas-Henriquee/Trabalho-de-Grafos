#ifndef GRAFO_BASICO_EDGE_HPP
#define GRAFO_BASICO_EDGE_HPP

#include "defines.hpp"

struct Edge
{
    Edge *_next_edge;
    float _weight;
    size_t _target_id;
};

#endif // GRAFO_BASICO_EDGE_HPP
