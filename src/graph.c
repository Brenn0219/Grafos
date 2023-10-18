#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"

int graph_edge_insertion(Graph *graph, int v, int w) {
    if(list_search(graph->adjacent[v], w))
        return 1;

    if(list_insert(graph->adjacent[v], NULL, w) == 0) {
        graph->ecount++;
        return 0;
    }
        
    return -1;
}

int graph_build(Graph *graph, char *path) {
    FILE *file = fopen(path, "r");
    int t_vertex, t_edge, v, w;

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    fscanf(file, "%d %d", &t_vertex, &t_edge);
    graph_init(graph, t_vertex);

    for(int i = 0; i < t_edge; i++) {
        if(fscanf(file, "%d %d", &v, &w) != EOF) 
            graph_edge_insertion(graph, v, w);
        else
            i = t_edge;
    }         

    fclose(file);
    return 0;
}

void graph_init(Graph *graph, int n) {
    graph->vcount = ++n;
    graph->ecount = 0;
    graph->adjacent = (Link *) malloc(sizeof(Link) * n);
    
    for(int i = 1; i < n; i++) {
        graph->adjacent[i] = (List *) malloc(sizeof(List));
        list_init(graph->adjacent[i]);
    }         
}