#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../include/graph.h"
#include "../include/list.h"
#include  "../include/stack.h"
#include "../include/print_graph.h"
#include "../include/dinic.h"

/// @brief Constroi um grafo ralicionando os vertive v e w. A construcao e feita aparti de uma leitura de um arquivo passando o caminho na variavel path. O arquivo tem que contar o total de vertice, total de aresta, seus relacionamentos e por fim o grafico ja tem que esta inicializado com a funcao graph_init. Complexidade - O(V+E)
/// @param graph ponteiro para um grafo
/// @param path caminho de um arquivo que contem os relacionamentos de um 
int build_graph(Graph *graph, const char *path) {
    FILE *file = fopen(path, "r");
    int v_count, e_count, v, w;
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    fscanf(file, "%d %d", &v_count, &e_count);
        
    for(int i = 0; i < e_count; i++) {
        if (fscanf(file, "%d %d", &v, &w) != EOF) {
            VertexWeight src = {.data = v, .weight = 1};
            VertexWeight dist = {.data = w, .weight = 1};

            graph_insert_vertex(graph, (void *)&src);
            graph_insert_vertex(graph, (void *)&dist);
            graph_insert_edge(graph, (void *)& src, (void *)& dist);
        } else 
            break;
    }
    
    fclose(file);
} 

int main() {
    Graph graph;
    char *path = "data/graph.txt";

    graph_init(&graph, sizeof(VertexWeight), vertex_macth, vertex_destroy);
    build_graph(&graph, path);

    const void *src = ((AdjList *) list_data(list_head(graph.adjlists)))->vertex;
    const void *dest = ((AdjList *) list_data(list_tail(graph.adjlists)))->vertex;

    dinic(&graph, src, dest);

    graph_destroy(&graph);
    
    return 0;
}