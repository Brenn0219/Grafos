#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"
#include  "../include/stack.h"
#include "../include/print_graph.h"
#include "../include/dfs.h"
#include "../include/edmonds.h"

/// @brief funcao de comparacao das estruturas usadas em lista e grafos
/// @param first_key primeira chave a ser comparada
/// @param second_key segunda chave a ser comparada
/// @param structure_size tamanho das estruturas para comparacao
/// @return 1 se for igual, 0 se forem diferentes e -1 ser for nulas
int macth(const void *first_key, const void *second_key) {
    WeightedVertex *v = (WeightedVertex *) (first_key);
    WeightedVertex *w = (WeightedVertex *) (second_key);

    if (v->vertice > w->vertice) 
        return 1;
    else if (v->vertice == w->vertice)
        return 0;
    else 
        return -1;
}

/// @brief funcao de liberar estruturas dinamicas da memoria
/// @param data dado a ser liberado
void destroy(void *data) {
    free(data);
}

/// @brief Constroi um grafo ralicionando os vertive v e w. A construcao e feita aparti de uma leitura de um arquivo passando o caminho na variavel path. O arquivo tem que contar o total de vertice, total de aresta, seus relacionamentos e por fim o grafico ja tem que esta inicializado com a funcao graph_init. Complexidade - O(V+E)
/// @param graph ponteiro para um grafo
/// @param path caminho de um arquivo que contem os relacionamentos de um 
int build_graph(Graph *graph, const char *path) {
    FILE *file = fopen(path, "r");
    int v_count, e_count, v, w, weight;
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    fscanf(file, "%d %d", &v_count, &e_count);
        
    for(int i = 0; i < e_count; i++) {
        if (fscanf(file, "%d %d %d", &v, &w, &weight) != EOF) {
            WeightedVertex v_vertex, w_vertex;
            
            v_vertex.vertice = v;
            w_vertex.vertice = w;
            v_vertex.weight = -1;
            w_vertex.weight = weight;

            graph_insert_vertex(graph, (void *)&v_vertex);
            graph_insert_vertex(graph, (void *)&w_vertex);
            graph_insert_edge(graph, (void *)& v_vertex, (void *)& w_vertex);
        } else 
            break;
    }
    
    fclose(file);
} 

/// @brief 
/// @param v 
/// @param w 
/// @return 
int comparison_weights(const void * v, const void *w) {
    WeightedVertex *first_key = (WeightedVertex *) (v);
    WeightedVertex *second_key = (WeightedVertex *) (w);

    if (first_key->weight > second_key->weight)
        return 1;
    else if (first_key->weight == second_key->weight)
        return 0;
}

int main() {
    Graph graph;
    Stack stack;   
    char *path = "data/graph-test.txt";

    graph_init(&graph, sizeof(WeightedVertex), macth, destroy);
    build_graph(&graph, path);

    Graph *spanning_aborescence = (Graph *) malloc(sizeof(Graph));
    WeightedVertex root;
    root.vertice = 5;
    edmonds(&graph, (void *) &root, spanning_aborescence, comparison_weights);
    
    graph_destroy(&graph);
    stack_destroy(&stack);

    return 0;
}