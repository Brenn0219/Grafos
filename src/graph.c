#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"

void graph_init(Graph *graph, size_t structure_size, int (*match) (const void *first_key, const void *second_key, size_t structure_size), void (*destroy) (void *data)) {
    graph->vcount = 0;
    graph->ecount = 0;
    graph->structure_size = structure_size;

    graph->match = match;
    graph->destroy = destroy;

    graph->adjlists = (List *) malloc(sizeof(List));
    list_init(graph->adjlists, sizeof(AdjList), NULL);
}

int graph_build(Graph *graph, char *path) {
    FILE *file = fopen(path, "r");
    int v_count, e_count, v, w;
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    fscanf(file, "%d %d", &v_count, &e_count);
    
    ++v_count;
    for(int i = 1; i < v_count; i++)  
        graph_insert_vertex(graph, (void *)&i);
    
    for(int i = 0; i < e_count; i++) {
        if (fscanf(file, "%d %d", &v, &w) != EOF) 
            graph_insert_edge(graph, (void *)&v, (void *)&w);
        else 
            break;
    }
    
    fclose(file);
}

void graph_destroy(Graph *graph) {
    AdjList *adjlist;

    while (list_size(graph->adjlists) > 0) {
        
        adjlist = (AdjList *) list_data(list_head(graph->adjlists));
        // list_destroy();
    }
    
}

int graph_insert_vertex(Graph *graph, const void *data) {
    AdjList *adjlist;
    int retval;

    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *) list_data(element))->vertex, graph_structure_size(graph)))
            return 1;
    }
    
    if ((adjlist = (AdjList *) malloc(sizeof(AdjList))) == NULL)
        return -1;
    
    if ((adjlist->adjacent = (List *) malloc(sizeof(List))) == NULL)
        return -1;

    adjlist->vertex = (void *) malloc(sizeof(int));
    memcpy(adjlist->vertex, data, graph_structure_size(graph));
    // memcpy(adjlist->vertex, data, sizeof(int));

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
        if (graph->match(w, ((AdjList *) list_data(element))->vertex, graph_structure_size(graph)))
            break;
    }
    
    if (element == NULL) 
        return -1;

    for(element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(v, ((AdjList *) list_data(element))->vertex, graph_structure_size(graph)))
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

    element = list_head(graph->adjlists);

    if (element == NULL)
        return -1;

    if (!graph->match(data, ((AdjList *) list_data(element))->vertex, graph_structure_size(graph))) {
        while (element != NULL) {
            if (element->next != NULL) {
                if (graph->match(data, ((AdjList *) list_data(element->next))->vertex, graph_structure_size(graph))) {
                    prev = element;
                    break;
                }
            } else 
                return -1;   

            element = list_next(element);
        }

        element = list_next(element);

        if (graph->match(((AdjList *) list_data(list_tail(graph->adjlists)))->vertex, ((AdjList *) list_data(element))->vertex, graph_structure_size(graph)))
            graph->adjlists->tail = prev;

        prev->next = element->next; 
        free(element->next); 
    } else 
        graph->adjlists->head = element->next;

    list_destroy(((AdjList *) list_data(element))->adjacent);
    free(((AdjList *) list_data(element))->vertex);
    free(((AdjList *) list_data(element))->adjacent);
    free(element->data);
    free(element);

    return 0;
}

int graph_remove_edge(Graph *graph, void *data1, void *data2) {
    Cell *element;

   
}