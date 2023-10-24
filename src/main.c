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
    if (first_key == NULL || second_key == NULL) 
        return -1;

    if (!memcmp(first_key, second_key, sizeof(Vertex)))
        return 1;

    return 0;
}

/// @brief funcao de liberar estruturas dinamicas da memoria
/// @param data dado a ser liberado
void destroy(void *data) {
    free(data);
}

int main() {
    Graph graph;
    char *path = "data/graph-test-100.txt";
    
    graph_init(&graph, sizeof(Vertex), macth, destroy);
    graph_build(&graph, path);
    
    Vertex v, w;
    v.vertice = 1;
    w.vertice = 43;
    graph_remove_edge(&graph, (void *) &v, (void *) &w);

    w.vertice = 10;
    graph_remove_edge(&graph, (void *) &v, (void *) &w);

    w.vertice = 2;
    graph_remove_edge(&graph, (void *) &v, (void *) &w);

    print_graph(&graph);

    return 0;
}