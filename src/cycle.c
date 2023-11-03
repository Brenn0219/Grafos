#include <stdlib.h>
#include <stdbool.h>
#include "../include/cycle.h"
#include "../include/vertex.h"

/// @brief 
/// @param list 
/// @param data 
/// @param match 
/// @return 
static Cell* search_father(List *list, const void *data, int (*match) (const void *first_key, const void *second_key)) {
    for(Cell *i = list_head(list); i != NULL; i = list_next(i)) {
        if(match(data, ((AdjList *) list_data(i))->vertex) == 0) 
            return i;
    }

    return NULL;
}

/// @brief 
/// @param graph 
/// @param element 
/// @param visited 
/// @param edge_to 
/// @param on_stack 
/// @param stack 
/// @return 
static int cycle(Graph *graph, void *element, bool *visited, int *edge_to, bool *on_stack, Stack *stack) {
    AdjList *adjlist;
    void *v, *w;
    int retval = 0;

    graph_adjlist(graph, element, &adjlist);
    v = adjlist->vertex;

    visited[vertex_data(v)] = true;
    on_stack[vertex_data(v)] = true;
    
    for (Cell *current = list_head(adjlist->adjacent); current != NULL; current = list_next(current)) {
        w = list_data(current);
    
        if (!visited[vertex_data(w)]) {
            edge_to[vertex_data(w)] = vertex_data(v);
            return cycle(graph, w, visited, edge_to, on_stack, stack);
        } else if (on_stack[vertex_data(w)]) {
            void *cycle_vertex = v;
            VertexWeight vertex_to;
            Cell *father;

            // inicializando a lista dos vertices que pertence ao ciclo
            stack_init(stack, graph_structure_size(graph), graph->destroy);

            // definindo o pai do primeiro vertice do ciclo
            vertex_to.data = edge_to[vertex_data(w)];
            father = search_father(graph->adjlists, (void *) &vertex_to, graph->match);

            // pesquisando o vertice no grafo
            for (Cell *i = list_head(((AdjList *) list_data(father))->adjacent); i != NULL; i = list_next(i)) {
                if (graph->match(list_data(i), w) == 0) {
                    w = list_data(i);
                    break;
                }
            }

            // inserindo os vertice do ciclo na lista
            while (graph->match(cycle_vertex, w) != 0) {
                if (stack_push(stack, cycle_vertex))
                    return -1;
        
                vertex_to.data = edge_to[vertex_data(cycle_vertex)];
                father = search_father(graph->adjlists, (void *) &vertex_to, graph->match);
                cycle_vertex = ((AdjList *) list_data(father))->vertex;
            }

            if (stack_push(stack, w))
                return -1;
            
            return 1;
        }
    }

    on_stack[vertex_data(v)] = false;
    visited[vertex_data(v)] = true;

    return retval;
}

/// @brief 
/// @param graph 
/// @param stack 
/// @return 
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
    
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        retval = cycle(graph, ((AdjList *) list_data(v))->vertex, visited, edge_to, on_statck, stack);
        
        if (retval == -1)
            perror("Error insertion Stack\n");
        else if (retval == 1)
            break;
    }
    
    free(visited);
    free(on_statck);
    free(edge_to);

    return retval; 
}