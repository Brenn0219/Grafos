#include <memory.h>
#include <stdbool.h>
#include "../include/edmonds.h"
#include "../include/print_graph.h"

/// @brief 
/// @param graph 
/// @param v 
/// @param w 
/// @return 
static int check_vertex_cycle(const Graph *graph, const Stack *stack, const void *vertex) {
    for (Cell *element = list_head(stack); element != NULL; element = list_next(element)) {
        if (graph->match(list_data(element), vertex) == 0)
            return 1;
    }

    return  0;
}

/// @brief 
/// @param graph 
/// @param stack 
/// @param spanning_aborescence 
/// @return 
static int contract_cycle(Graph *graph, Stack *stack, Graph *spanning_aborescence) {
    AdjList new_vertex;
    
    // inicializa o novo grafo
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);

    // novo vertice fica identificado com o primeiro da stack (ciclo)
    new_vertex.vertex = list_data(list_head(stack));

    if (graph_insert_vertex(spanning_aborescence, new_vertex.vertex) == -1)
        return -1;

    // inserir os vertices no grafo ignorando os do ciclo  
    int v_cycle = 0, w_cycle = 0;
    void *u = NULL, *p = NULL; 
    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        u = ((AdjList *) list_data(element))->vertex;
        p = list_data(list_head(((AdjList *) list_data(element))->adjacent));

        v_cycle = check_vertex_cycle(graph, stack, u);
        w_cycle = check_vertex_cycle(graph, stack, p);
        
        if (!v_cycle && !w_cycle) {
            if (graph_insert_vertex(spanning_aborescence, u) == -1)
                return -1;

            if (graph_insert_vertex(spanning_aborescence, p) == -1)
                return -1;

            if (graph_insert_edge(spanning_aborescence, u, p) == -1)
                return -1;
        } else if (!v_cycle && w_cycle) {
            if (graph_insert_vertex(spanning_aborescence, u) == -1)
                return -1;

            if (graph_insert_edge(spanning_aborescence, u, new_vertex.vertex) == -1)
                return -1;
        }
    }

    print_graph(spanning_aborescence);

    return 0;
}

/// @brief 
/// @param graph 
/// @param root 
/// @param spanning_aborescence 
/// @param comparison_weights 
/// @return 
static int edmonds_main(Graph *graph, const void *root, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {
    Stack stack;

    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        void *smaller = NULL;
        Cell *v = NULL;

        for (Cell *w = list_head(((AdjList *) list_data(element))->adjacent); w != NULL; w = list_next(w)) {
            if (v == NULL)
                smaller = list_data(w);
            else if (comparison_weights(list_data(v), list_data(w)))
                smaller = list_data(v);
        }
        
        if (smaller == NULL)
            return -1;
        if (graph_insert_vertex(spanning_aborescence, ((AdjList *) list_data(element))->vertex) == -1)
            return -1;
        
        if (graph_insert_vertex(spanning_aborescence, smaller) == -1)
            return -1;
        
        if (graph_insert_edge(spanning_aborescence, ((AdjList *) list_data(element))->vertex ,smaller) == -1)
            return -1;
    }

    int retval = graph_has_cycle(spanning_aborescence, &stack);
    if (retval || retval != -1) {
        Graph *new_graph = (Graph *) malloc(sizeof(Graph));
        
        contract_cycle(spanning_aborescence, &stack, new_graph);

        spanning_aborescence = new_graph;
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