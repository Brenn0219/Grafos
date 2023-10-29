#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"
#include "../include/stack.h"

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
        if (!graph->match(data, ((AdjList *) list_data(element))->vertex))
            return element;
    }

    return NULL;
}

static int cylce(Graph *graph, void *element, bool *visited, int *edge_to, bool *on_stack, Stack *stack) {
    AdjList *adjlist;
    void *v, *w;
    int retval = 0;

    graph_adjlist(graph, element, &adjlist);
    v = adjlist->vertex;

    visited[((Vertex *) v)->vertice] = true;
    on_stack[((Vertex *) v)->vertice] = true;
    
    for (Cell *current = list_head(adjlist->adjacent); current != NULL; current = list_next(current)) {
        w = list_data(current);
    
        if (!visited[((Vertex *) w)->vertice]) {
            edge_to[((Vertex *) w)->vertice] = ((Vertex *) v)->vertice;
            return cylce(graph, w, visited, edge_to, on_stack, stack);
        } else if (on_stack[((Vertex *) w)->vertice]) {
            void *cycle_vertex = v;
            stack_init(stack, graph_structure_size(graph), graph->destroy);
            
            while (graph->match(cycle_vertex, w) != 0) {
                if (stack_push(stack, cycle_vertex))
                    return -1;
                ((Vertex *) cycle_vertex)->vertice = edge_to[((Vertex *) cycle_vertex)->vertice];
            }
            if (stack_push(stack, w))
                return -1;
            
            return 1;
        }
    }

    on_stack[((Vertex *) v)->vertice] = false;
    visited[((Vertex *) v)->vertice] = true;

    return retval;
}

int graph_has_cycle(Graph *graph, Stack *stack) {
    int n = graph->vcount + 1, retval = 0;
    int *edge_to = (int *) malloc(sizeof(int) * n);
    bool *visited = (bool *) malloc(sizeof(bool) * n),
        *on_statck = (bool *) malloc(sizeof(bool) * n);

    for (int i = 1; i < n; i++) {
        edge_to[i] = 0;
        visited[i] = false;
        on_statck[i] = false;
    }
    
    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        retval = cylce(graph, ((AdjList *) list_data(element))->vertex, visited, edge_to, on_statck, stack);
        
        if (retval == -1)
            perror("Error insertion Stack\n");
        else 
            break;
    }
    
    free(visited);
    free(on_statck);
    free(edge_to);

    return retval; 
}