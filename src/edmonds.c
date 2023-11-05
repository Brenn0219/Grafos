#include <memory.h>
#include <stdbool.h>
#include "../include/edmonds.h"
#include "../include/graph.h"
#include "../include/print_graph.h"

/// @brief Compara dois inteiros
/// @param first Um ponteiro para o primeiro inteiro a ser comparado
/// @param second Um ponteiro para o segundo inteiro a ser comparado
/// @return Retorna 0 se os inteiros forem diferentes, ou 1 se eles forem iguais.
static int compare_integer(const void *first, const void *second) {
    if (!memcmp(first, second, sizeof(int)))
        return 1;
    return 0;
}

/// @brief Checa se uma aresta do grafo contraído corresponde a uma aresta do grafo original e atualiza os pesos correspondentes
/// @param graph Um ponteiro para a estrutura do grafo original
/// @param src Um ponteiro para os dados da fonte da aresta que está sendo checada
/// @param dest Um ponteiro para onde os dados da aresta destino serão atualizados se uma correspondência for encontrada
/// @return Retorna um inteiro indicando se a correspondência foi encontrada e os dados foram atualizados
static int verify_edge(const Graph *graph, const void *src, void *dest)
 {
    AdjList *adjlist = NULL;
    
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        if (graph->match(((AdjList *) list_data(v))->vertex, src) == 0) {
            adjlist = (AdjList *) list_data(v);
            break;
        }
    }

    if (adjlist == NULL)
        return 0;
    
    for (Cell *w = list_head(adjlist->adjacent); w != NULL; w = list_next(w)) {
        if (graph->match(list_data(w), dest) == 0) {
            ((VertexWeight *) dest)->weight = vertex_weight(list_data(w));
            return 1;
        }
    }

    return 0;
}

/// @brief Expande ciclos dentro de uma árvore de abrangência para reconstruir a árvore de abrangência original.
/// @param graph Um ponteiro para o grafo original onde o ciclo foi identificado.
/// @param aborescence Um ponteiro para o grafo que representa a árvore de abrangência atual, que será atualizada ao expandir o ciclo.
/// @param cycle Um ponteiro para uma pilha contendo os vértices que formam o ciclo a ser expandido.
/// @param n O número total de vértices no grafo.
/// @param parents Um array que representa os pais dos vértices na árvore de abrangência; será atualizado durante a expansão do ciclo.
/// @param weights Um array que contém os pesos das arestas na árvore de abrangência; será ajustado para refletir as mudanças após a expansão do ciclo.
/// @return Retorna um inteiro indicando o sucesso (geralmente 0 para sucesso e -1 para falha) da operação de expansão do ciclo.
static int expand_cycle(const Graph *graph, Graph *aborescence, Stack *cycle, int n, int *parents, int *weights) {
    int *head = stack_peek(cycle), vth, node, target;
    bool visited[n];

    if (head != NULL)
        vth = parents[*head];

    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjList = (AdjList *) list_data(v);

        if (graph_insert_vertex(aborescence, adjList->vertex) == -1)
            return -1;
    }
    
    for (int i = 1; i < n; i++) {
        target = i;
        node = parents[target];
        
        while (node != 0 && !visited[target]) {
            VertexWeight v = {.data = node, .weight = weights[node]};
            VertexWeight w = {.data = target, .weight = weights[target]};

            if (verify_edge(graph, (void *) &v, (void *) &w)) {
                if (head != NULL) {
                    if (!compare_integer((void *) &vth, (void *) &vertex_data(&v))
                        && !compare_integer((void *) head, (void *) &vertex_data(&w))) {
                        if (!verify_edge(aborescence, (void *) &v, (void *) &w)) {
                            if (graph_insert_edge(aborescence, (void *) &v, (void *) &w) == -1)
                                return -1;
                        }
                    }
                } else {
                    if (!verify_edge(aborescence, (void *) &v, (void *) &w)) {
                        if (graph_insert_edge(aborescence, (void *) &v, (void *) &w) == -1)
                            return -1;
                    }
                }
            }

            visited[target] = true;
            target = node;
            node = parents[target];
        }

        visited[target] = true;
    }
}

/// @brief Contrai um ciclo no grafo, criando um novo grafo onde o ciclo é representado por um único nó
/// @param graph Um ponteiro para a estrutura do grafo original no qual o ciclo foi detectado
/// @param contracted_graph Um ponteiro para a estrutura do grafo onde o grafo com o ciclo contraído será armazenado
/// @param cycle Uma pilha contendo os vértices que formam o ciclo a ser contraído
/// @param weights Um ponteiro para um vetor de pesos associados às arestas do grafo original
/// @return Retorna um inteiro que normalmente indica sucesso ou falha na operação de contração do ciclo
static int contract_cycle(const Graph *graph, Graph *contracted, Stack *cycle, const int *weights) {
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

                if (graph_insert_vertex(contracted, (void *) &u) == -1)
                    return -1;

                if (graph_insert_vertex(contracted, (void *) &p) == -1)
                    return -1;

                if (graph_insert_edge(contracted, (void *) &u, (void *) &p) == -1)
                    return -1;
            }
        }
    }

    return 0;
}

/// @brief Detecta um ciclo no grafo a partir de um dado índice
/// @param parents Um ponteiro para um vetor de inteiros que representa os predecessores de cada vértice no grafo
/// @param index O índice do vértice a partir do qual a busca por um ciclo começa
/// @param cycle Um ponteiro para uma estrutura de pilha onde os vértices que formam o ciclo serão armazenados
/// @return Retorna um inteiro que normalmente indica se um ciclo foi encontrado ou alguma outra condição definida pelo implementador
static int cycle(const int* parents, const int index, Stack *cycle) {
    Stack aux;
    int father;

    stack_init(&aux, sizeof(int), compare_integer, NULL);
    stack_push(&aux, (void *) &index);

    father = parents[index];
    while (father != 0) {
        if (stack_search(&aux, (void *) &father)) {
            while (!compare_integer(&father, stack_peek(&aux))) {
                stack_push(cycle, stack_peek(&aux));
                stack_pop(&aux);
            }

            stack_push(cycle, &father);

            return 1;
        } else {
            stack_push(&aux, &father);
            father = parents[father];
        }
    }
    
    return 0;
}

/// @brief Descobre ciclo no grafo com base nos predecessores
/// @param n O número de vértices no grafo
/// @param parents Um ponteiro para um vetor de inteiros contendo os predecessores de cada vértice
/// @param stack Um ponteiro para uma estrutura de pilha utilizada para armazenar os vértices do ciclo descoberto
/// @return Retorna um inteiro que pode indicar a presença de um ciclo ou alguma outra condição definida pelo implementador
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

/// @brief Encontra os predecessores de peso mínimo para cada vértice
/// @param graph Um ponteiro para a estrutura do grafo no qual o algoritmo opera
/// @param weights Um ponteiro para um vetor de inteiros onde os pesos mínimos de entrada serão armazenados
/// @param v_min Um ponteiro para um vetor de inteiros onde os índices dos predecessores de peso mínimo serão armazenados
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

/// @brief Método principal de Edmonds, recursivo
/// @param graph Um ponteiro para a estrutura do grafo no qual o algoritmo opera
/// @param aborescence Um ponteiro para a estrutura do grafo onde a arborescência de extensão mínima será armazenada
/// @param contracted Um ponteiro para a estrutura do grafo que contém os vértices e arestas contratados durante o processo recursivo
/// @param n O tamanho (número de vértices) do grafo original (graph)
static void edmonds_main(const Graph *graph, Graph *aborescence, Graph *contracted, const int n) {
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
        edmonds_main(graph, aborescence, &new_graph, n);
    }

    expand_cycle(graph, aborescence, &stack, n, v_min, weights);
}

void edmonds(Graph *graph, Graph *aborescence) {    
    graph_init(aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    edmonds_main(graph, aborescence, graph, graph->vcount + 1);
}