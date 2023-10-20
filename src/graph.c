#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/list.h"

void graph_init(Graph *graph, int (*match) (const void *first_key, const void *second_key), void (*destroy) (void *data)) {
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;
    graph->adjlists = (List *) malloc(sizeof(List));
    list_init(graph->adjlists, NULL);
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
    for(int i = 1; i < v_count; i++) {
        graph_insert_vertex(graph, i); 
    }
    
    for(int i = 0; i < e_count; i++) {
        if (fscanf(file, "%d %d", &v, &w) != EOF) {
            graph_insert_edge(graph, v, w);
        } else 
            break;
    }
    
    fclose(file);
}

int graph_insert_vertex(Graph *graph, const void *data) {
    AdjList *adjlist;
    int retval;

    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *) list_data(element))->vertex))
            return 1;
    }
    
    if ((adjlist = (AdjList *) malloc(sizeof(AdjList))) == NULL)
        return -1;
    
    adjlist->vertex = data;
    list_init(&adjlist->adjacent, NULL);
    
    if ((retval = list_insert(graph->adjlists, list_tail(graph->adjlists), adjlist)) != 0) 
        return retval;
    
    graph->vcount++;

    return 0;
}

int graph_insert_edge(Graph *graph, const void *v, const void *w) {
    Cell *element;
    int retval;

    for(element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(w, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL) 
        return -1;

    for(element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(v, ((AdjList *) list_data(element))->vertex))
            break;
    }

    if (element == NULL) 
        return -1;

    if ((retval = list_insert(&((AdjList *) list_data(element))->adjacent, NULL, w)) != 0)
        return retval;
    
    graph->ecount++;

    return 0;
}

int graph_remove_vertex(Graph *graph, void **data) {
    Cell *temp, *prev = NULL;
    List *list;
    int found = 0;   

    for(Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        // is member

        if (graph->match(*data, list_data(element))) {
            temp = element;
            found = 1;
        }

        if (!found)
            prev = element;
    }

    if (!found) 
        return -1;

    if (list_size((List *)list_data(temp)) > 0)
        return -1;

    if (list_remove(graph->adjlists, prev, (void **) list) != 0)
        return -1;
    
    free(list);

    graph->vcount--;

    return 0;
}