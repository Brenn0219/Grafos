#pragma once

#include "graph.h"

typedef struct FlowVertex {
    int data;
    int flux;
    int capacity;
} FlowVertex;

/// @brief 
/// @param graph 
/// @param residual 
int build_residual_graph(const Graph *graph, Graph *residual);

/// @brief 
/// @param v 
/// @param w 
/// @return 
int match_residual(const void *first_key, const void *second_key);

/// @brief 
/// @param residual 
/// @param path 
void increasing_path(const Graph *residual, List *path);

/// @brief 
/// @param v 
void print_residual_graph(const void *v);