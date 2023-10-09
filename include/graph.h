#pragma once
#include <stdio.h>

// estrutura de no da lista
typedef struct node {
    int vertex;
    struct node *next;
} node;

// ponteiro para a estrutura de dados node
typedef struct node *link; 

// grafos
typedef struct graph {
    int vertex; 
    int edge;
    link *adjacent;
} graph;

// instanciando um novo no
node* new_node(int x);
// inserindo as relacoes dos vertices - arestas
void insert_edge(graph *graph, int v, int w);
// construindo o grafico
void build_graph(graph *graph, char *path);
// grau dos vertices sucessores
int degree_vertex_sucessor_set(graph graph, int vertex);
// grau dos vertices predecessores
int degree_vertex_predecessor_set(graph graph, int vertex);
// maior grau entre os vertices
int highest_degree_vertex(graph directedGraph, char derection, int *vertex);

// estrutura de tabela da dfs
typedef struct table {
    int *descoveryTime;
    int *endTime;
    int *father;
} table;

// ordenacao do conjunto de sucessores de um determinado vertice - select
void ordering(int set[], int n);
// retorna o numero de sucessores de um conjunto
int set_size(node *n);
// criando o conjunto de sucessores de um determinado vertice
void lexographic_set(int set[], node *node, int n);
// busca em profundidade 
void depeth_search(graph graph, table table, int vertex, int *lifetime);
// inicializacao da busca em profundidade
table dfs(graph graph);
