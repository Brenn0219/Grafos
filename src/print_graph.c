#include "../include/graph.h"
#include "../include/list.h"
#include "../include/dfs.h"

// print do conjunto dos sucessores de um veritice
void print_successors_set(Graph graph, int v) {
    printf("sucessors = {");
    for(Cell *i = list_head(graph.adjacent[v]); i != NULL; i = list_next(i)) 
        printf("%d - ", list_data(i));
    printf("\n");
}

// print do conjunto dos predecessores de um veritice
void print_predecessor_set(Graph graph, int v) {
    int n = graph.vcount + 1;

    printf("predecessors = {");
    for(int i = 1; i < n; i++) {
        if(i != v) {
            for(Cell *j = list_head(graph.adjacent[i]); j != NULL; j = list_next(j)) {
                if(list_data(j) == v) {
                    printf("%d - ", i);
                    break;
                }
            }
        }
    }
    printf("}\n");
}

// print do conjunto de uma das "direcoes"
void print_vertex_set(Graph directedGraph, int v, char derection) {
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

    print(directedGraph, v);
}

// classificacao das arestas de um vertice especifico
void print_edge_classification(int v, Graph graph, DfsTable table) {
    printf("=============================================\n");

    for(Cell *i = list_head(graph.adjacent[v]); i != NULL; i = list_next(i)) {
        if (v == table.father[list_data(i)]) {
            printf("{%d, %d} - arvore\n", v, list_data(i));
        } else if(table.end[v] < table.end[list_data(i)] && table.start[v] > table.start[list_data(i)]) {
            printf("{%d, %d} - retorno\n", v, list_data(i));
        } else if (table.start[v] < table.start[list_data(i)]) {
            printf("{%d, %d} - avanco\n", v, list_data(i));
        } else {
            printf("{%d, %d} - cruzamento\n", v, list_data(i));
        }
    }
}