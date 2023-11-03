#include <stdio.h>
#include <stdlib.h>
#include "../include/vertex.h"

void vertex_print(const void *v) {
    printf("%d(%d)", vertex_data(v), vertex_weight(v));
}

int vertex_macth(const void *first_key, const void *second_key) {
    VertexWeight *v = (VertexWeight *) (first_key);
    VertexWeight *w = (VertexWeight *) (second_key);

    if (v->data > w->data) 
        return 1;
    else if (v->data == w->data)
        return 0;
    else 
        return -1;
}

int vertex_comparison_weights(const void *v, const void *w) {
    int v_weight = vertex_weight(v);
    int w_weight = vertex_weight(w);

    if (v > w)
        return 1;
    else if (v == w)
        return 0;
    return -1;
}

/// @brief funcao de liberar estruturas dinamicas da memoria
/// @param data dado a ser liberado
void vertex_destroy(void *v) {
    free(v);
}