#pragma once

#include "../include/graph.h"
#include "../include/list.h"

/// @brief Estrutura de dados de Tabela em Busca Profundidade
typedef struct DfsTable {
    int *start;
    int *end;
    int *father;
} DfsTable;

/// @brief Destroi a tabela de busca em profundidade
/// @param table ponteiro para uma tabela de busca em profundidade
void dfs_table_free(DfsTable *table);

/// @brief Inicializacao da tabela de busca em profundidade
/// @param table ponteiro para uma tabela de busca em profundidade
/// @param n total de vertices do grafo
void dfs_table_init(DfsTable *table, int n);

/// @brief Algoritmo reliza uma busca em um grafo, onde encontra o vertice mais recente e classifica as arestas
/// @param graph ponteiro para um grafo
/// @param table ponteiro para uma tabela de busca em profundidade
void graph_dfs(Graph *graph, DfsTable *table);