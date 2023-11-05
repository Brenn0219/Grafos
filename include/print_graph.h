#pragma once
#include "graph.h"

/// @brief Imprime uma representação do grafo.
/// @param graph Um ponteiro para o grafo que será impresso.
/// @param print Uma função ponteiro que sabe como imprimir um único vértice do grafo.
void print_graph(const Graph *graph, void (*print) (const void *v));