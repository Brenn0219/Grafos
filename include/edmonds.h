#pragma once

#include "graph.h"

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @param comparison_weights 
void edmonds(Graph *graph, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w));