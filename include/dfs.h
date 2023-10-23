#pragma once

#include "../include/graph.h"
#include "../include/list.h"

/// @brief Estrutura de Dados de Vertice da Busca em profundidade
typedef struct DfsVertex {
    void *data;
    VertexColor color;
} DfsVertex;

/// @brief Uma busca é dita em profundidade quando o critério de escolha de vértice marcado for dentre todos os vértices marcados e incidentes a alguma aresta ainda não explorada, escolher aquele mais recentemente alcançado na busca. 
/// @param graph ponteiro para um grafo
/// @param ordered ponteiro para lista que e inicializada no metodo, que contem os vertice da busca
/// @return Retorna uma lista com as buscas em profundidade
int dfs(Graph *graph, List *ordered);