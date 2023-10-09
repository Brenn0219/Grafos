#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"

// instanciando um novo no
node* new_node(int x) {
    node *node = malloc(sizeof(struct node));
    node->vertex = x;
    node->next = NULL;

    return node;
}

// inserindo as relacoes dos vertices - arestas
void insert_edge(graph *graph, int v, int w) {
    node *i = graph->adjacent[v];
       
    while (i != NULL) {
        if(i->vertex == w) 
            return;

        if(i->next == NULL) 
            break;
        else 
            i = i->next;
    }
    
    i->next = new_node(w);
    graph->edge++;
}

// construindo o grafico
void build_graph(graph *graph, char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int vertex, edge, v, w;
    fscanf(file, "%d %d", &vertex, &edge);
    
    graph->vertex = vertex;
    graph->edge = 0;
    graph->adjacent = malloc(sizeof(link) * (vertex + 1));
    
    for(int i = 1; i < vertex + 1; i++) {
        graph->adjacent[i] = malloc(sizeof(struct node));
        graph->adjacent[i]->vertex = i;
        graph->adjacent[i]->next = NULL;  
    }
    
    while (fscanf(file, "%d %d", &v, &w) != EOF) {
        insert_edge(graph, v, w);  
    }

    fclose(file);
}

// grau dos vertices sucessores
int degree_vertex_sucessor_set(graph graph, int vertex) {
    node *i = graph.adjacent[vertex]->next;
    int counter = 0;

    while (i != NULL) {
        counter++;
        i = i->next;
    }
    
    return counter;
}

// grau dos vertices predecessores
int degree_vertex_predecessor_set(graph graph, int vertex) {
    int n = graph.vertex + 1, counter = 0;

    for(int i = 1; i < n; i++) {
        if (i != vertex) {
            node *j = graph.adjacent[i]->next;

            while (j != NULL) {
                if(j->vertex == vertex) {
                    counter++;
                }

                j = j->next;
            }
        }
    }

    return counter;
}

// maior grau entre os vertices
int highest_degree_vertex(graph directedGraph, char derection, int *vertex) {
    int (*degree)(graph, int); // ponteiro par uma funcao
    
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

// ordenacao do conjunto de sucessores de um determinado vertice - select
void ordering(int set[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(set[j] < set[i]) {
                int temp = set[j];
                set[j] = set[i];
                set[i] = temp;
            }
        }
    }
}

// retorna o numero de sucessores de um conjunto
int set_size(node *n) {
    int counter = 0;

    for(node *i = n->next; i != NULL; i = i->next) {
        counter++;
    }
    
    return counter;
}

// criando o conjunto de sucessores de um determinado vertice
void lexographic_set(int set[], node *node, int n) {
    for(int i = 0; i < n; i++) {
        set[i] = node->vertex;
        node = node->next;
    }
}

// busca em profundidade 
void depeth_search(graph graph, table table, int vertex, int *lifetime) {
    int n = set_size(graph.adjacent[vertex]);
    int set[n];
    
    lexographic_set(set, graph.adjacent[vertex]->next, n);
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
table dfs(graph graph) {
    int n = graph.vertex + 1, lifetime = 0;
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
