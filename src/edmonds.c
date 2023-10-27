#include "../include/edmonds.h"
#include <memory.h>

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @param comparison_weights 
static int edmonds_main(Graph *graph, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {
    AdjList *element = (AdjList *)(list_data(list_head(graph->adjlists)));

    while (element != NULL) {
        void *smaller = NULL;
        Cell *v = list_head(element->adjacent);

        for (Cell *w = list_next(v); w != NULL; w = list_next(w)) {
            if (comparison_weights(v, w))
                smaller = v->data;
            
            list_next(v);
        }

        if (smaller == NULL)
            return -1;

        if (graph_insert_vertex(spanning_aborescence, smaller) == -1)
            return -1;

        if (graph_insert_edge(spanning_aborescence, element->vertex ,smaller) == -1)
            return -1;

        element = graph_vertex_search(graph, smaller);
    }
}

void edmonds(Graph *graph, const void *root, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {    
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    graph_insert_vertex(spanning_aborescence, root);

    edmonds_main(graph, spanning_aborescence, comparison_weights);
}