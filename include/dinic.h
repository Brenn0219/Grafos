#pragma once

#include "graph.h"

/// @brief 
/// @param graph 
/// @param src 
/// @param dest 
void dinic(const Graph *graph, const void* home, const void* target);