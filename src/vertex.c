#include <stdio.h>
#include "../include/vertex.h"

void vertex_print(const void *v) {
    printf("%d(%d)", vertex_data((VertexWeight *) v), vertex_weight((VertexWeight *) v));
}

int vertex_comparison_weights(const void *v, const void *w) {
    int v_weight = vertex_weight((VertexWeight *) v);
    int w_weight = vertex_weight((VertexWeight *) w);

    if (v > w)
        return 1;
    else if (v == w)
        return 0;
    return -1;
}