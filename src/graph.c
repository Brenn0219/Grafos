#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"

void graph_init(Graph *graph, size_t structure_size, int (*match) (const void *first_key, const void *second_key), void (*destroy) (void *data)) {
    graph->vcount = 0;
    graph->ecount = 0;
    graph->structure_size = structure_size;

    graph->match = match;
    graph->destroy = destroy;

    graph->adjlists = (List *) malloc(sizeof(List));
    list_init(graph->adjlists, sizeof(AdjList), NULL);
}

void graph_destroy(Graph *graph) {
    Cell *element = list_head(graph->adjlists);

    while (element != NULL) {
        Cell *prev = element;
        
        list_destroy(((AdjList *) list_data(prev))->adjacent);
        free(((AdjList *) list_data(prev))->vertex);
        free(((AdjList *) list_data(prev))->adjacent);
        free(prev->data);
        
        element = list_next(prev);
        
        free(prev);
        
    }

    free(graph->adjlists);
    memset(graph, 0, sizeof(Graph));
}

int graph_insert_vertex(Graph *graph, const void *data) {
    AdjList *adjlist;
    int retval;

    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(data, ((AdjList *) list_data(element))->vertex))
            return 1;
    }
    
    if ((adjlist = (AdjList *) malloc(sizeof(AdjList))) == NULL)
        return -1;
    
    if ((adjlist->adjacent = (List *) malloc(sizeof(List))) == NULL)
        return -1;

    adjlist->vertex = (void *) malloc(graph_structure_size(graph));
    memcpy(adjlist->vertex, data, graph_structure_size(graph));

    list_init(adjlist->adjacent, graph_structure_size(graph), graph->destroy);
    if ((retval = list_insert(graph->adjlists, list_tail(graph->adjlists), adjlist)) != 0) 
        return retval;
    
    graph->vcount++;

    return 0;
}

int graph_insert_edge(Graph *graph, const void *v, const void *w) {
    Cell *element;
    int retval;

    for(element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(w, ((AdjList *) list_data(element))->vertex))
            break;
    }
    
    if (element == NULL) 
        return -1;

    for(element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(v, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL) 
        return -1;
    
    if ((retval = list_insert(((AdjList *) list_data(element))->adjacent, NULL, w)) != 0)
        return retval;

    graph->ecount++;

    return 0;
}

int graph_remove_vertex(Graph *graph, void *data) {
    Cell *element, *prev = NULL;

    for (element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(data, ((AdjList *) list_data(element))->vertex))
            break;
        prev = element;
    }

    if (element == NULL)
        return -1;

    ((AdjList *) list_data(element))->adjacent->destroy(((AdjList *) list_data(element))->vertex);
    list_destroy(((AdjList *) list_data(element))->adjacent);
    free(element->data);    
    list_remove(graph->adjlists, prev);

    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        List *list = ((AdjList *) list_data(v))->adjacent;
        prev = NULL;

        for (Cell *w = list_head(list); w != NULL; w = list_next(w)) {
            if (!graph->match(data, w->data)) {
                if (list_remove(list, prev) == -1)
                    return -1;
            }

            prev = w;
        }   
    }

    graph->vcount--;

    return 0;
}

int graph_remove_edge(Graph *graph, void *v, void *w) {
    List *list;
    Cell *element, *prev = NULL;

    for (element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(v, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL)
        return -1;

    list = ((AdjList *) list_data(element))->adjacent;
    for (element = list_head(list); element != NULL; element = list_next(element)) {
        if (!graph->match(w, element->data))
            break;
        
        prev = element;
    }

    if (element == NULL)
        return -1;

    if (list_remove(list, prev) == -1)
        return -1;

    graph->ecount--;

    return 0;
}

int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist) {
    Cell *element, *prev = NULL;

    for (element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(data, ((AdjList *) list_data(element))->vertex))
            break;
        
        prev = element;
    }

    if (element == NULL)
        return -1;

    *adjlist = list_data(element);
    
    return 0;
}

void* graph_vertex_search(const Graph *graph, const void *data) {
    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (!graph->match(element->data, data))
            return element;
    }

    return NULL;
}