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
/// @param x 
/// @param y 
/// @return 
static int search_edge(const Graph *graph, const void *x, void *y) {
    AdjList *adjlist = NULL;
    
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        if (graph->match(((AdjList *) list_data(v))->vertex, x) == 0) {
            adjlist = (AdjList *) list_data(v);
            break;
        }
    }

    if (adjlist == NULL)
        return 0;
    
    for (Cell *w = list_head(adjlist->adjacent); w != NULL; w = list_next(w)) {
        if (graph->match(list_data(w), y) == 0) {
            ((VertexWeight *) y)->weight = vertex_weight(list_data(w));
            return 1;
        }
    }

    return 0;
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @param cycle 
/// @param n 
/// @param perents 
/// @param weights 
/// @return 
static int expand_cycle(const Graph *graph, Graph *spanning_aborescence, Stack *cycle, int n, int *perents, int *weights) {
    int *head = stack_peek(cycle), vth, node, target;
    bool visited[n];

    if (head != NULL)
        vth = perents[*head];

    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjList = (AdjList *) list_data(v);

        if (graph_insert_vertex(spanning_aborescence, adjList->vertex) == -1)
            return -1;
    }
    
    for (int i = 1; i < n; i++) {
        target = i;
        node = perents[target];
        
        while (node != 0 && !visited[target]) {
            VertexWeight v = {.data = node, .weight = weights[node]};
            VertexWeight w = {.data = target, .weight = weights[target]};

            if (search_edge(graph, (void *) &v, (void *) &w)) {
                if (head != NULL) {
                    if (!compare_integer((void *) &vth, (void *) &vertex_data(&v))
                        && !compare_integer((void *) head, (void *) &vertex_data(&w))) {
                        if (!search_edge(spanning_aborescence, (void *) &v, (void *) &w)) {
                            if (graph_insert_edge(spanning_aborescence, (void *) &v, (void *) &w) == -1)
                                return -1;
                        }
                    }
                } else {
                    if (!search_edge(spanning_aborescence, (void *) &v, (void *) &w)) {
                        if (graph_insert_edge(spanning_aborescence, (void *) &v, (void *) &w) == -1)
                            return -1;
                    }
                }
            }

            visited[target] = true;
            target = node;
            node = perents[target];
        }

        visited[target] = true;
    }
}

/// @brief 
/// @param graph 
/// @param stack 
/// @return 
static int contract_cycle(const Graph *graph, Graph *contracted_graph, Stack *cycle, const int *weights) {
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
static void find_min_parents(const Graph *graph, int *weights, int *v_min) {
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
/// @param contracted 
/// @param n 
static void edmonds_main(const Graph *graph, Graph *spanning_aborescence, Graph *contracted, const int n) {
    Stack stack;
    int weights[n], v_min[n];

    memset((void *) weights, 0, sizeof(int) * n);
    memset((void *) v_min, 0, sizeof(int) * n);
    stack_init(&stack, sizeof(int), compare_integer, NULL);

    find_min_parents(contracted, weights, v_min);

    if (discover_cycle(n, v_min, &stack)) {
        Graph new_graph;
        graph_init(&new_graph, graph_structure_size(graph), graph->match, graph->destroy);

        contract_cycle(contracted, &new_graph, &stack, weights);
        edmonds_main(graph, spanning_aborescence, &new_graph, n);
    }

    expand_cycle(graph, spanning_aborescence, &stack, n, v_min, weights);
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
void edmonds(Graph *graph, Graph *spanning_aborescence) {    
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    edmonds_main(graph, spanning_aborescence, graph, graph->vcount + 1);
    
    printf("G\n");
    print_graph(graph, vertex_print);
    printf("\n=====================================\n");

    printf("AGM\n");
    print_graph(spanning_aborescence, vertex_print);
}