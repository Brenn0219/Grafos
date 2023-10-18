#pragma once
#include <stdio.h>
#include "list.h"

/// @brief Ponteiro para a estrutura de dado Lista
typedef struct List *Link;

/// @brief Estrutura de dado de grafos. O atributo vcount e o total de vertices do grafo, ecount o total de arestas do grafo e adjacent e uma lista encadeada correspondendo a cada vertice
typedef struct Graph {
    int vcount; 
    int ecount;
    Link *adjacent;
} Graph;

/// @brief Insere uma aresta em um grafo
/// @param graph ponteiro para um grafo 
/// @param v vertice fonte
/// @param w vertice sucessor - destino
/// @return 1 se aresta (v, w) ja foi inserida; 0 aresta inserida com sucesso; -1 caso algo de errado
int graph_edge_insertion(Graph *graph, int v, int w);

/// @brief Construi um grafico a partir de um arquivo. Instancia todas os vertices e insere as arestas fornecidas no arquivo
/// @param graph ponteiro para grafo
/// @param path caminho para abertura do arquivo
/// @return 0 grafico construido com sucesso; -1 se nao encontrar o arquivo de abertura 
int graph_build(Graph *graph, char *path);

/// @brief Inicializacao de um grafo. Define atributos vcount e ecount para 0, e inicializa a estruta da lista 
/// @param graph ponteiro para um grafo
/// @param n total de vertices do grafo de inicio
void graph_init(Graph *graph, int n);