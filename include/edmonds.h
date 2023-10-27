#pragma once

#include "graph.h"

/// @brief 
/// @param graph 
/// @param root 
/// @param spanning_aborescence 
/// @param comparison_weights 
void edmonds(Graph *graph, const void *root, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w));