#pragma once

typedef struct Vertex {
    int vertice;
} Vertex;

typedef struct VertexWeight  {
    int data;
    int weight;
} VertexWeight;

typedef enum VertexColor {
    WHITE, 
    GRAY, 
    BLACK
} VertexColor;

/// @brief imprime um vertice
/// @param v ponteiro para um vertice
void vertex_print(const void *v);

/// @brief funcao de comparacao dos vertices
/// @param first_key primeira chave a ser comparada
/// @param second_key segunda chave a ser comparada
/// @param structure_size tamanho das estruturas para comparacao
/// @return 1 se for igual, 0 se forem diferentes e -1 ser for nulas
int vertex_macth(const void *first_key, const void *second_key);

/// @brief compara os pesos de dois vertices
/// @param v ponteiro para um vertice
/// @param w ponteiro para um vertice
/// @return 1 se v > w, 0 se v == w e -1 se v < w 
int vertex_comparison_weights(const void *v, const void *w);

/// @brief funcao de liberar estruturas dinamicas da memoria
/// @param v vertice a ser liberado
void vertex_destroy(void *v);

#define vertex_data(v) (((VertexWeight *) v)->data)
#define vertex_weight(v) (((VertexWeight *) v)->weight)