#pragma once

#include "graph.h"

typedef struct BfsVertex  {
    void *data;
    VertexColor color;
    int hops;
} BfsVertex;
