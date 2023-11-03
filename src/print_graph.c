#include "../include/print_graph.h"
#include "../include/graph.h"
#include "../include/list.h"

void print_graph(const Graph *graph, void (* print) (const void *v)) {
    
    for(Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);
        printf("%d - ", vertex_data(adjlist->vertex));

        for(Cell *i = list_head(adjlist->adjacent); i != NULL; i = list_next(i)) {
            print(list_data(i));
            printf(" - ");
        }

        printf("\n");
    }
}