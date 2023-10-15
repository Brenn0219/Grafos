#include "../include/graph.h"

// print do conjunto dos sucessores de um veritice
void print_successors_set(Graph graph, int vertex) {
    Node *i = graph.adjacent[vertex]->next;

    printf("sucessors = {");
    while (i != NULL) {
        if(i->next != NULL) {
            printf("%d - ", i->vertex);
        } else {
            printf("%d}\n", i->vertex);
        }

        i = i->next;
    }
}

// print do conjunto dos predecessores de um veritice
void print_predecessor_set(Graph graph, int vertex) {
    int n = graph.vertex + 1;

    printf("predecessors = {");
    for(int i = 1; i < n; i++) {
        if(i != vertex) {
            Node *j = graph.adjacent[i]->next;

            while (j != NULL) {
                if(j->vertex == vertex) {
                    printf("%d - ", i);
                    break;
                }

                j = j->next;
            }
            
        }
    }
    printf("}\n");
}

// print do conjunto de uma das "direcoes"
void print_vertex_set(Graph directedGraph, int vertex, char derection) {
    void (*print)(Graph, int);

    switch (derection) {
        case 'p':
            print = print_predecessor_set;
            break;
        case 's':
            print = print_successors_set;
            break;
        default:
            break;
    }

    print(directedGraph, vertex);
}

// classificacao das arestas de um vertice especifico
void print_edge_classification(int vertex, Graph graph, table table) {
    int n = set_size(graph.adjacent[vertex]);
    int set[n];

    lexographic_set(set, graph.adjacent[vertex]->next, n);

    printf("=============================================\n");

    for(int i = 0; i < n; i++) {
        if (vertex == table.father[set[i]]) {
            printf("{%d, %d} - arvore\n", vertex, set[i]);
        } else if(table.endTime[vertex] < table.endTime[set[i]] && table.descoveryTime[vertex] > table.descoveryTime[set[i]]) {
            printf("{%d, %d} - retorno\n", vertex, set[i]);
        } else if (table.descoveryTime[vertex] < table.descoveryTime[set[i]]) {
            printf("{%d, %d} - avanco\n", vertex, set[i]);
        } else {
            printf("{%d, %d} - cruzamento\n", vertex, set[i]);
        }
    }
}