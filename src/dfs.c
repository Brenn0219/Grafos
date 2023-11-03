#include <stdlib.h>
#include "../include/list.h"
#include "../include/graph.h"
#include "../include/dfs.h"

static int dfs_main(Graph *graph, AdjList *adjlist, List *ordered) {
    AdjList *clr_adjlist;
    DfsVertex *clr_vertex;
    Cell *member;

    ((DfsVertex *) adjlist->vertex)->color = GRAY;

    for (member = list_head(adjlist->adjacent); member != NULL; member = list_next(member)) {
        if (graph_adjlist(graph, list_data(member), &clr_adjlist) != 0)
            return -1;

        clr_vertex = clr_adjlist->vertex;

        if (clr_vertex->color == WHITE) {
            if (dfs_main(graph, clr_adjlist, ordered) != 0)
                return -1;
        }
    }

    ((DfsVertex *) adjlist->vertex)->color = BLACK;
    
    if (list_insert(ordered, NULL, (DfsVertex *) adjlist->vertex) != 0)
        return -1;
    
    return 0;
}

int dfs(Graph *graph, List *ordered) {
    DfsVertex *vertex;
    Cell *element;

    for (element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        vertex = ((AdjList *) list_data(element))->vertex;
        vertex->color = WHITE;
    }

    list_init(ordered, graph_structure_size(graph), graph->match, graph->destroy);

    for (element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        vertex = ((AdjList *) list_data(element))->vertex;

        if (vertex->color == WHITE) {
            if ((dfs_main(graph, (AdjList *) list_data(element), ordered)) != 0 ) {
                list_destroy(ordered);
                return -1;
            }
        }
    }

    return 0;
}