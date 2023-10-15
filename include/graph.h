#pragma once
#include <stdio.h>

// estrutura de no da lista
typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

// ponteiro para a estrutura de dados node
typedef struct Node *link; 

// grafos
typedef struct Graph {
    int vertex; 
    int edge;
    link *adjacent;
} Graph;

// instanciando um novo no
Node* new_node(int x);
// inserindo as relacoes dos vertices - arestas
void insert_edge(Graph *graph, int v, int w);
// construindo o grafico
void build_graph(Graph *graph, char *path);
// grau dos vertices sucessores
int degree_vertex_sucessor_set(Graph graph, int vertex);
// grau dos vertices predecessores
int degree_vertex_predecessor_set(Graph graph, int vertex);
// maior grau entre os vertices
int highest_degree_vertex(Graph directedGraph, char derection, int *vertex);

// estrutura de tabela da dfs
typedef struct table {
    int *descoveryTime;
    int *endTime;
    int *father;
} table;

// ordenacao do conjunto de sucessores de um determinado vertice - select
void ordering(int set[], int n);
// retorna o numero de sucessores de um conjunto
int set_size(Node *n);
// criando o conjunto de sucessores de um determinado vertice
void lexographic_set(int set[], Node *node, int n);
// busca em profundidade 
void depeth_search(Graph graph, table table, int vertex, int *lifetime);
// inicializacao da busca em profundidade
table dfs(Graph graph);
