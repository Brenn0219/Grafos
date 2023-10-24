#include "../include/print_graph.h"
#include "../include/graph.h"
#include "../include/list.h"

void print_graph(Graph *graph) {
    
    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        printf("%d: ", ((Vertex *)(((AdjList *) list_data(element))->vertex))->vertice);

        for(Cell *i = list_head(((AdjList *) list_data(element))->adjacent); i != NULL; i = list_next(i))
            printf("%d -", ((Vertex *)(i->data))->vertice);
        printf("\n");
    }
}