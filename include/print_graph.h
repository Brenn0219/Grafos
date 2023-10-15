#pragma once
#include "graph.h"

// print do conjunto dos sucessores de um veritice
void print_successors_set(Graph graph, int vertex);
// print do conjunto dos predecessores de um veritice
void print_predecessor_set(Graph graph, int vertex);
// print do conjunto de uma das "direcoes"
void print_vertex_set(Graph directedGraph, int vertex, char derection);
// classificacao das arestas de um vertice especifico
void print_edge_classification(int vertex, Graph graph, table table);