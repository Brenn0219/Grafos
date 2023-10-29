#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"
#include  "../include/stack.h"
#include "../include/print_graph.h"
#include "../include/dfs.h"

/// @brief funcao de comparacao das estruturas usadas em lista e grafos
/// @param first_key primeira chave a ser comparada
/// @param second_key segunda chave a ser comparada
/// @param structure_size tamanho das estruturas para comparacao
/// @return 1 se for igual, 0 se forem diferentes e -1 ser for nulas
int macth(const void *first_key, const void *second_key) {
    Vertex *v = (Vertex *) (first_key);
    Vertex *w = (Vertex *) (second_key);

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
int graph_build(Graph *graph, const char *path) {
    FILE *file = fopen(path, "r");
    int v_count, e_count, v, w, weight;
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    fscanf(file, "%d %d", &v_count, &e_count);
        
    for(int i = 0; i < e_count; i++) {
        if (fscanf(file, "%d %d", &v, &w) != EOF) {
            Vertex v_vertex, w_vertex;
            
            v_vertex.vertice = v;
            w_vertex.vertice = w;
            // v_vertex.weight = -1;
            // w_vertex.weight = weight;

            graph_insert_vertex(graph, (void *)&v_vertex);
            graph_insert_vertex(graph, (void *)&w_vertex);
            graph_insert_edge(graph, (void *)& v_vertex, (void *)& w_vertex);
        } else 
            break;
    }
    
    fclose(file);
} 

int main() {
    Stack stack;   
    Vertex v, *w;
    int size;

    stack_init(&stack, sizeof(Vertex), destroy);

    for (int i = 1; i < 11; i++) {
        v.vertice = i;
        stack_push(&stack, (void *) &v);
    }
    
    for (Cell *i = list_head(&stack); i != NULL; i = list_next(i))
        printf("%d - ", ((Vertex *) list_data(i))->vertice);
    printf("\n");

    for (int i = 0; i < 3; i++)
        stack_pop(&stack);

    for (Cell *i = list_head(&stack); i != NULL; i = list_next(i))
        printf("%d - ", ((Vertex *) list_data(i))->vertice);
    printf("\n");
    
    w = (Vertex *) stack_peek(&stack);
    size = stack_size(&stack);
    printf("size: %d\n", size);

    stack_destroy(&stack);

    return 0;
}