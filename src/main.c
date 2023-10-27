#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"
#include "../include/print_graph.h"
#include "../include/dfs.h"

/// @brief funcao de comparacao das estruturas usadas em lista e grafos
/// @param first_key primeira chave a ser comparada
/// @param second_key segunda chave a ser comparada
/// @param structure_size tamanho das estruturas para comparacao
/// @return 1 se for igual, 0 se forem diferentes e -1 ser for nulas
int macth(const void *first_key, const void *second_key) {
    WeightedVertex *v = (WeightedVertex *) (first_key);
    WeightedVertex *w = (WeightedVertex *) (second_key);

    if (v->vertice > w->vertice) 
        return 1;
    else if (v->vertice == w->vertice)
        return 0;
    else 
        return -1;
}

/// @brief funcao de liberar estruturas dinamicas da memoria
/// @param data dado a ser liberado
void destroy(void *data) {
    free(data);
}

int main() {
    Graph graph;
    char *path = "data/graph-test-weighted.txt";
    
    graph_init(&graph, sizeof(WeightedVertex), macth, destroy);
    graph_build(&graph, path);
    
    WeightedVertex v, w;
    v.vertice = 1;
    w.vertice = 4;
    graph_remove_edge(&graph, (void *) &v, (void *) &w);

    w.vertice = 2;
    graph_remove_edge(&graph, (void *) &v, (void *) &w);

    v.vertice = 3;
    graph_remove_vertex(&graph, (void *) &v);

    print_graph(&graph);
    graph_destroy(&graph);

    return 0;
}