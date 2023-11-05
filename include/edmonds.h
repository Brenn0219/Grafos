#pragma once

#include "graph.h"

/// @brief Encontra uma arborescência de extensão mínima de um grafo direcionado
/// @param graph Um ponteiro para a estrutura do grafo no qual o algoritmo opera
/// @param spanning_aborescence Um ponteiro para a estrutura do grafo onde o resultado será armazenado
void edmonds(Graph *graph, Graph *spanning_aborescence);