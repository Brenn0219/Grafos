#pragma once
#include <stdio.h>
#include "list.h"

/// @brief Estrutura de dados Grafos, são compostos por dois tipos de elementos: vértices e arestas. Vértices representam objetos, e as bordas estabelecem relacionamentos ou conexões entre os objetos
typedef struct Graph {
    int vcount; 
    int ecount;
    size_t structure_size;

    int (*match) (const void *first_key, const void *second_key);
    void (*destroy) (void *data);

    List *adjlists;
} Graph;

/// @brief Estrutura de dados Lista Adjacencia são usadas para grafos esparsos, ou seja, grafos nos quais o número de arestas é menor que o número de vértices ao quadrado.
typedef struct AdjList {
    void *vertex;
    List *adjacent;
} AdjList;

/// @brief Estrutura de Vertice usada nas pesquisas dfs e bfs
typedef enum VertexColor {
    WHITE, 
    GRAY, 
    BLACK
} VertexColor;

/// @brief Estrutura de Vertice no grafo
typedef struct Vertex {
    int vertice;
} Vertex;

/// @brief Estrutura de Vertices que cada lista adjacente tem um vertice com peso. ex: v - w, w armazena o peso desta relacao
typedef struct WeightedVertex {
    int vertice;
    int weight;
} WeightedVertex;

/// @brief Inicializa o grafico especificado por graph. Esta operacao deve ser chamada para um grafico antes que o grafico possa ser usado com qualquer outra operacao. O argumento match e uma funcao usada por varias operacaoes graficas para determinar se dois vertices correspondem. Deve retornar 1 se first_key for igual second_key e caso contrario. O argumento destroy fornece uma maneira de liberar dados alocados dinamicamente quando graph_destroy e chamado graph_destroy. Para por exemplo, se o gráfico contiver dados alocados dinamicamente usando malloc, destroy devera ser definido como free para libere os dados enquanto o gráfico é destruído. Para dados estruturados contendo vários alocados dinamicamente membros, destroy deve ser definido como uma funçao definida pelo usuario que chama free para cada membro alocado dinamicamente. membro, bem como para a propria estrutura. Para um grafico contendo dados que não devem ser liberados, destrua deve ser definido como NULL. Complexidade - O(1)
/// @param graph ponteiro para um grafo
/// @param structure_size tamanho da estrutura utilizada na lista
/// @param match ponteiro para funcao de comparacao entre as estruturas alocadas na lista
/// @param destroy ponteiro para funcao de liberacao das estruturas alocadas dinamicamente nas listas
void graph_init(Graph *graph, size_t structure_size, int (*match) (const void *first_key, const void *second_key), void (*destroy) (void *data));

/// @brief Constroi um grafo ralicionando os vertive v e w. A construcao e feita aparti de uma leitura de um arquivo passando o caminho na variavel path. O arquivo tem que contar o total de vertice, total de aresta, seus relacionamentos e por fim o grafico ja tem que esta inicializado com a funcao graph_init. Complexidade - O(V+E)
/// @param graph ponteiro para um grafo
/// @param path caminho de um arquivo que contem os relacionamentos de um 
int graph_build(Graph *graph, const char *path);

/// @brief Destrói o gráfico especificado por graph . Nenhuma outra operação é permitida após chamar graph_destroy a menos que graph_init seja chamado novamente. A operação graph_destroy remove todos os vértices e arestas de um gráfico e chama a função passada como destroy para graph_init uma vez para cada vértice ou aresta à medida que é removido, desde que destroy não tenha sido definido como NULL.
/// @param graph ponteiro para um grafo
void graph_destroy(Graph *graph);

/// @brief Insere um vértice no gráfico especificado por graph. O novo vértice contém um ponteiro para data, então o a memória referenciada pelos dados deve permanecer válida enquanto o vértice permanecer no gráfico. É o responsabilidade do chamador gerenciar o armazenamento associado aos dados. Complexidade - O(V), onde V é o número de vértices no gráfico.
/// @param graph ponteiro para um grafo
/// @param data novo elemento a ser inserido na lista
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário
int graph_insert_vertex(Graph *graph, const void *data);

/// @brief Insere uma aresta do vértice especificado por data1 até o vértice especificado por data2 no gráfico especificado pelo gráfico. Ambos os vértices devem ter sido inseridos anteriormente usando graph_insert_vertex . O novo edge é representado com um ponteiro para data2 na lista de adjacências do vértice especificado por data1 , então a memória referenciada por data2 deve permanecer válida enquanto a aresta permanecer no gráfico. É o responsabilidade do chamador gerenciar o armazenamento associado aos dados2. Para inserir uma aresta (u , v ) em um gráfico não direcionado, chame esta operação duas vezes: uma vez para inserir uma aresta de u a v e novamente para inserir o borda implícita de v para você . Este tipo de representação é comum para gráficos não direcionados. Complexidade - O(V), onde V é o número de vértices no gráfico.
/// @param graph ponteiro para um grafo
/// @param data1 vertice incidente
/// @param data2 vertice sucessor
/// @return 0 se a remocao da aresta for bem-sucedidae, -1 caso contrário.
int graph_insert_edge(Graph *graph, const void *data1, const void *data2);

/// @brief Remove os dados de correspondência de vértices do gráfico especificado por graph . Todas as arestas incidentes de e para o vértice deve ter sido removido anteriormente usando graph_remove_edge . Ao retornar, os dados apontam para o dados armazenados no vértice que foi removido. É responsabilidade do chamador gerenciar o armazenamento associado aos dados. Complexidade - O (V + E ), onde V é o número de vértices no gráfico e E é o número de arestas.
/// @param graph ponteiro para um grafo
/// @param data vertice a ser removido
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário.
int graph_remove_vertex(Graph *graph, void *data);

/// @brief Remove a borda de v para w no gráfico especificado por graph . No retorno, w aponta para os dados armazenados na lista de adjacências do vértice especificado por v . É responsabilidade de o chamador para gerenciar o armazenamento associado aos dados.
/// @param graph ponteiro para um grafo
/// @param v vertice incidente
/// @param w vertice sucessor
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário.
int graph_remove_edge(Graph *graph, void *v, void *w);

/// @brief Recupera vértices adjacentes ao vértice especificado pelos dados em graph . Os vértices adjacentes são retornado na forma de uma estrutura AdjList, uma estrutura contendo os dados de correspondência de vértices e um conjunto de vértices adjacentes a ele. Um ponteiro para a lista de adjacências real no grafo é retornado, portanto não deve ser manipulado pelo chamador. Complexidade - O (V), onde V é o número de vértices no gráfico.
/// @param graph ponteiro para um grafo
/// @param data vertice 
/// @param adjlist lista adjacente do vertice/data
/// @return 1 se o segundo vértice for adjacente ao primeiro vértice ou caso contrário.
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);

// Macro que retorna a lista encadeada utilizada no grafo
#define graph_adjlists(graph) ((graph)->adjlists)
// Macro que retorna o valor da estrutura que ira ser utilizada na lista do grafo
#define graph_structure_size(graph) ((graph)->structure_size)
// Macro que avalia o número de vértices no gráfico especificado por graph.
#define graph_vcount(graph) ((graph)->vcount)
// Macro que avalia o número de arestas no gráfico especificado por gráfico.
#define graph_ecount(graph) ((graph)->ecount)