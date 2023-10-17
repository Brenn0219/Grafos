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


// grau dos vertices predecessores
int degree_vertex_predecessor_set(Graph graph, int vertex) {
    int n = graph.vcount + 1, counter = 0;

    for(int i = 1; i < n; i++) {
        if (i != vertex) {
            Cell *j = list_head(graph.adjacent[i]);

            while (j != NULL) {
                if(j->data == vertex)
                    counter++;
                j = j->next;
            }
        }
    }

    return counter;
}

// maior grau entre os vertices
int highest_degree(Graph graph, char derection, int *vertex) {
    int (*degree)(Graph, int); // ponteiro par uma funcao
    
    switch (derection) {
        case 'p':
            degree = degree_vertex_predecessor_set;
            break;
        case 's':
            degree = degree_vertex_sucessor_set;
            break;
        default:
            break;
    }

    int n = directedGraph.vertex + 1, highestDegree = 0, x = 0;

    for(int i = 1; i < n; i++) {
        x = degree(directedGraph, directedGraph.adjacent[i]->vertex);

        if(highestDegree < x) {
            highestDegree = x;
            *vertex = i;
        }
    }

    return highestDegree;
}

// busca em profundidade 
void depeth_search(Graph graph, table table, int vertex, int *lifetime) {
    int n = list_size(graph.adjacent[vertex]), counter = 0;
    int set[n];

    for(Cell *i = list_head(graph.adjacent[vertex]); i != NULL; i = list_next(i)) 
        set[counter++] = i->data;

    ordering(set, n);

    table.descoveryTime[vertex] = ++*lifetime;

    for(int i = 0; i < n; i++) {
        if(table.descoveryTime[set[i]] == 0) {
            table.father[set[i]] = vertex;
            printf("{%d, %d} - arvore\n", vertex, set[i]);
            depeth_search(graph, table, set[i], lifetime);
        } 
    }

    table.endTime[vertex] = ++*lifetime;
}

// inicializacao da busca em profundidade
table dfs(Graph graph) {
    int n = graph.vcount + 1, lifetime = 0;
    table table;

    table.descoveryTime = (int *) malloc(sizeof(int) * n);
    table.endTime = (int *) malloc(sizeof(int) * n);
    table.father = (int *) malloc(sizeof(int) * n);

    for(int i = 1; i < n; i++) {
        table.descoveryTime[i] = 0;
        table.endTime[i] = 0;
        table.father[i] = -1;
    }

    depeth_search(graph, table, 1, &lifetime);

    return table;
}