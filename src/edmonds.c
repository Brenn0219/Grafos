#include "../include/edmonds.h"
#include <memory.h>
#include <stdbool.h>

/// @brief 
/// @param graph 
/// @param stack 
/// @param spanning_aborescence 
/// @return 
static int contract_cycle(Graph *graph, Stack *stack, Graph *spanning_aborescence) {
    AdjList *new_vertex;
    
    // inicializa o novo grafo
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    
    // novo vertice fica identificado com o primeiro da stack (ciclo)
    memcpy(new_vertex->vertex, list_head(stack)->data, list_structure_size(stack));
    
    // inserir todos os vertices que nao estao no ciclo
    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        if ((list_search(stack, ((AdjList *) list_data(element))->vertex) == NULL) && graph_insert_vertex(spanning_aborescence, ((AdjList *) list_data(element))->vertex) == -1)
            return -1;
    }
    
    if (graph_insert_vertex(spanning_aborescence, new_vertex->vertex) == -1)
        return -1;
    
    // inseirir arestas - O(n³)
    void *v, *w;
    Cell *prev = NULL;

    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        v = list_search(stack, ((AdjList *) list_data(element))->vertex);

        for (Cell *i = list_head(((AdjList *) list_data(element))->adjacent); i != NULL; i = list_next(i)) {
            w = list_search(stack, ((AdjList *) list_data(i))->vertex);

            if (v == NULL && w != NULL) {
                if (prev != NULL) {
                    ((WeightedVertex *) w)->weight = ((WeightedVertex *) w)->weight - ((WeightedVertex *) ((AdjList *) list_data(prev))->vertex)->weight;
                    graph_insert_edge(spanning_aborescence, ((AdjList *) v)->vertex, w);
                }
            } else
                graph_insert_edge(spanning_aborescence, ((AdjList *) v)->vertex, ((AdjList *) w)->vertex);
        }

        prev = element;
    }

    graph_destroy(graph);
    free(graph);

    return 0;
}

/// @brief 
/// @param graph 
/// @param root 
/// @param spanning_aborescence 
/// @param comparison_weights 
/// @return 
static int edmonds_main(Graph *graph, const void *root, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {
    AdjList *element;
    Stack stack;
    graph_adjlist(graph, root, &element);

    while (element != NULL) {
        AdjList smaller;
        Cell *v = list_head(element->adjacent);
        
        for (Cell *w = list_next(v); w != NULL; w = list_next(w)) {            
            if (comparison_weights(list_data(v), list_data(w)))
                smaller.vertex = v->data;

            list_next(v);
        }
        
        if (smaller.vertex == NULL)
            return -1;
        
        if (graph_insert_vertex(spanning_aborescence, element->vertex) == -1)
            return -1;
        
        if (graph_insert_vertex(spanning_aborescence, smaller.vertex) == -1)
            return -1;
        
        if (graph_insert_edge(spanning_aborescence, element->vertex ,smaller.vertex) == -1)
            return -1;
        
        element = graph_vertex_search(graph, (void *) &smaller);
    }
    
    int retval = graph_has_cycle(spanning_aborescence, &stack);
    if (retval || retval != -1) {
        Graph *new_graph = (Graph *) malloc(sizeof(Graph));
        contract_cycle(spanning_aborescence, &stack, graph);
        spanning_aborescence = new_graph;
    } else {
        
    }
}

/// @brief 
/// @param graph 
/// @param root 
/// @param spanning_aborescence 
/// @param comparison_weights 
void edmonds(Graph *graph, const void *root, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {    
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    
    edmonds_main(graph, root, spanning_aborescence, comparison_weights);
}