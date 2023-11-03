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

/// @brief compara os pesos de dois vertices
/// @param v ponteiro para um vertice
/// @param w ponteiro para um vertice
/// @return 1 se v > w, 0 se v == w e -1 se v < w 
int vertex_comparison_weights(const void *v, const void *w);

#define vertex_data(v) (((VertexWeight *) v)->data)
#define vertex_weight(v) (((VertexWeight *) v)->weight)