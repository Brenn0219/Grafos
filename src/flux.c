#include <stdlib.h>
#include "../include/flux.h"

int build_residual_graph(const Graph *graph, Graph *residual) {
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);
        FlowVertex src = {.data = vertex_data(adjlist->vertex), .flux = 0, .capacity = vertex_weight(adjlist->vertex)};

        if (graph_insert_vertex(residual, (void *) &src) == -1)
            return -1;

        for (Cell *w = list_head(adjlist->adjacent); w != NULL; w = list_next(w)) {
            FlowVertex dist = {.data = vertex_data(list_data(w)), .flux = 0, .capacity = vertex_weight(list_data(w))};

            if (graph_insert_vertex(residual, (void *) &dist) == -1)
                return -1;

            if (graph_insert_edge(residual, (void *) &src, (void *) &dist) == -1)     
                return -1;
        } 
    }
}

int match_residual(const void *first_key, const void *second_key) {
    FlowVertex *v = (FlowVertex *) (first_key);
    FlowVertex *w = (FlowVertex *) (second_key);

    if (v->data > w->data) 
        return 1;
    else if (v->data == w->data)
        return 0;
    else 
        return -1;
}

void print_residual_graph(const void *data) {
    FlowVertex *v = (FlowVertex *) data;

    printf("%d(%d/%d)", v->data, v->flux, v->capacity); 
}