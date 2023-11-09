#include <stdlib.h>
#include "../include/flux.h"
#include "../include/dinic.h"
#include "../include/queue.h"
#include "../include/bfs.h"
#include "../include/print_graph.h"

/// @brief 
/// @param residual 
/// @param start 
/// @param layered 
/// @return 
static int tiered_network(const Graph *residual, const void *start, Graph *layered) {
    Queue queue;
    BfsVertex *clr_vertex;
    AdjList *adjlist, *clr_adjlist;

    for (Cell *v = list_head(residual->adjlists); v != NULL; v = list_next(v)) {
        clr_vertex = ((AdjList *) list_data(v))->vertex;

        if (residual->match(clr_vertex, start) == 0) {
            clr_vertex->color = GRAY;
            clr_vertex->hops = 0;
        } else {
            clr_vertex->color = WHITE;
            clr_vertex->hops = -1;
        }
    }

    queue_init(&queue, sizeof(AdjList), NULL, NULL);

    if (graph_adjlist(residual, start, &clr_adjlist) == -1) {
        queue_destroy(&queue);
        return -1;
    }

    if (queue_enqueue(&queue, clr_adjlist) == -1) {
        queue_destroy(&queue);
        return -1;
    }
    
    while (queue_size(&queue) > 0) {
        adjlist = queue_peek(&queue);

        if (graph_insert_vertex(layered, adjlist->vertex) == -1)
            return -1;

        for (Cell *w = list_head(adjlist->adjacent); w != NULL; w = list_next(w)) {
            list_data(w);

            if (graph_adjlist(residual,  list_data(w), &clr_adjlist) == -1) {
                queue_destroy(&queue);
                return -1;
            }   

            clr_vertex = clr_adjlist->vertex;

            if (clr_vertex->color == WHITE) {
                clr_vertex->color = GRAY;
                clr_vertex->hops = ((BfsVertex *) adjlist->vertex)->hops + 1;

                if (queue_enqueue(&queue, clr_adjlist) == -1) {
                    queue_destroy(&queue);
                    return -1;
                }

                if (graph_insert_vertex(layered, list_data(w)) == -1)
                    return -1;

                if (graph_insert_edge(layered, adjlist->vertex, list_data(w)) == -1)
                    return -1;
            }
        }

        if (queue_dequeue(&queue) == 0)
            ((BfsVertex *) adjlist->vertex)->color = BLACK;
        else {
            queue_destroy(&queue);
            return -1;
        }
    }
}

void dinic_main(const Graph *graph, Graph *residual) {
    Graph layered;
    const FlowVertex *fv = (FlowVertex *) ((AdjList *) list_data(list_head(residual->adjlists)))->vertex;

    graph_init(&layered, graph_structure_size(residual), residual->match, residual->destroy);
    tiered_network(residual, (void *) fv, &layered);
}

void dinic(Graph *graph) {
    Graph residual;

    graph_init(&residual, sizeof(FlowVertex), match_residual, vertex_destroy);
    build_residual_graph(graph, &residual);

    dinic_main(graph, &residual);
}