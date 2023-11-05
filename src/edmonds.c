#include <memory.h>
#include <stdbool.h>
#include "../include/edmonds.h"
#include "../include/graph.h"
#include "../include/print_graph.h"

/// @brief 
/// @param x 
/// @param y 
/// @return 
static int compare_integer(const void *x, const void* y) {
    if (!memcmp(x, y, sizeof(int)))
        return 1;
    return 0;
}

/// @brief 
/// @param graph 
/// @param cycle 
/// @param contracted_graph 
/// @return 
static int expand_cycle(Graph *graph, Graph *contracted_graph, Graph *spanning_aborescence, Stack *cycle, int *perents, int *weights) {
    if (list_size(cycle) == 0)
        return 0;
    
    int top = *((int *)(list_data(list_head(cycle))));
    int edge_top = perents[top], n = graph->vcount + 1, x;

    VertexWeight p = {.data = top, .weight = weights[top]};
    VertexWeight w = {.data = edge_top, .weight = weights[edge_top]};

    if (graph_remove_edge(graph, (void *) &w, (void *) &p) == -1)
        return -1;
    
    perents[top] = 0;
    weights[top] = 0;
    
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);
        Cell *i = list_head(adjlist->adjacent);

        while (i != NULL) {
            if (compare_integer((void *) &perents[vertex_data(list_data(i))], (void *) &vertex_data(adjlist->vertex)) == 0) {
                p.data = vertex_data(adjlist->vertex); 
                p.weight = vertex_weight(adjlist->vertex);
                w.data = vertex_data(list_data(i));
                w.weight = vertex_weight(list_data(i));

                i = list_next(i);
                
                if (graph_remove_edge(graph, (void *) &p, (void *) &w) == -1)
                    return -1;
            } else
                i = list_next(i);
        }
    }
}

/// @brief 
/// @param graph 
/// @param stack 
/// @param spanning_aborescence 
/// @return 
static int contract_cycle(const Graph *graph, Graph *contracted_graph, Graph *spanning_aborescence, Stack *cycle, const int *weights) {
    int contracted_vertex = vertex_data(stack_peek(cycle));

    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);

        for (Cell *i = list_head(adjlist->adjacent); i != NULL; i = list_next(i)) {
            const VertexWeight *w = (VertexWeight *) list_data(i);

            if (stack_search(cycle, (void *) &vertex_data(adjlist->vertex)) && stack_search(cycle, (void *) &vertex_data(w))) 
                continue;
            else {
                VertexWeight u = {.data = vertex_data(adjlist->vertex), .weight = vertex_weight(adjlist->vertex)};
                VertexWeight p = {.data = vertex_data(w), .weight = vertex_weight(w)};

                if (stack_search(cycle, (void *) &vertex_data(adjlist->vertex)) && !stack_search(cycle, (void *) &vertex_data(w)))
                    u.data = contracted_vertex;
                else if (!stack_search(cycle, (void *) &vertex_data(adjlist->vertex)) && stack_search(cycle, (void *) &vertex_data(w))) {
                    p.data = contracted_vertex;
                    p.weight = p.weight - weights[vertex_data(w)];
                }

                if (graph_insert_vertex(contracted_graph, (void *) &u) == -1)
                    return -1;

                if (graph_insert_vertex(contracted_graph, (void *) &p) == -1)
                    return -1;

                if (graph_insert_edge(contracted_graph, (void *) &u, (void *) &p) == -1)
                    return -1;
            }
        }
    }

    return 0;
}

/// @brief 
/// @param parents 
/// @param index 
/// @param stack 
/// @return 
static int cycle(const int* parents, const int index, Stack *stack) {
    Stack aux;
    int father;

    stack_init(&aux, sizeof(int), compare_integer, NULL);
    stack_push(&aux, (void *) &index);

    father = parents[index];
    while (father != 0) {
        if (stack_search(&aux, (void *) &father)) {
            while (!compare_integer(&father, stack_peek(&aux))) {
                stack_push(stack, stack_peek(&aux));
                stack_pop(&aux);
            }

            stack_push(stack, &father);

            return 1;
        } else {
            stack_push(&aux, &father);
            father = parents[father];
        }
    }
    
    return 0;
}

/// @brief 
/// @param n 
/// @param parents 
/// @param stack 
/// @return 
static int discover_cycle(const int n, const int* parents, Stack *stack) {
    int retval = 0;
    stack_init(stack, sizeof(int), compare_integer, NULL);

    for (int i = 1; i < n; i++) {
        retval = cycle(parents, i, stack);

        if (retval)
            break;
    }

    return retval; 
}

/// @brief 
/// @param graph 
/// @param weights 
/// @param v_min 
/// @return 
static int find_min_parents(const Graph *graph, int *weights, int *v_min) {
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);

        for (Cell *i = list_head(adjlist->adjacent); i != NULL; i = list_next(i)) {
            const void *vertex = list_data(i);

            if (weights[vertex_data(vertex)]) {
                if (vertex_weight(vertex) < weights[vertex_data(vertex)]) {
                    weights[vertex_data(vertex)] = vertex_weight(vertex);
                    v_min[vertex_data(vertex)] = vertex_data(adjlist->vertex); 
                }
            } else {
                weights[vertex_data(vertex)] = vertex_weight(vertex);
                v_min[vertex_data(vertex)] = vertex_data(adjlist->vertex);
            }
        }
    }
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @return 
static int edmonds_main(Graph *graph, Graph *spanning_aborescence) {
    Stack stack;
    int n = graph->vcount + 1;
    int weights[n], v_min[n];

    memset((void *) weights, 0, sizeof(int) * n);
    memset((void *) v_min, 0, sizeof(int) * n);
    stack_init(&stack, sizeof(int), compare_integer, NULL);

    find_min_parents(graph, weights, v_min);

    for (int i = 1; i < n; i++) 
        printf("i: %d | perents: %d weight: %d\n", i, v_min[i], weights[i]);
    printf("\n");

    if (discover_cycle(n, v_min, &stack)) {
        Graph contracted_graph;
        graph_init(&contracted_graph, graph_structure_size(graph), graph->match, graph->destroy);

        contract_cycle(graph, &contracted_graph, spanning_aborescence, &stack, weights);

        for(Cell *element = list_head(&stack); element != NULL; element = list_next(element))
            printf("%d - ", *((int *) list_data(element)));
        printf("\n\n");
        print_graph(&contracted_graph, vertex_print);
        printf("\n=====================================\n");

        edmonds_main(&contracted_graph, spanning_aborescence);
        expand_cycle(graph, &contracted_graph, spanning_aborescence, &stack, v_min, weights);
    }
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
void edmonds(Graph *graph, Graph *spanning_aborescence) {    
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    print_graph(graph, vertex_print);
    printf("\n=====================================\n");
    edmonds_main(graph, spanning_aborescence);
}