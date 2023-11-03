#include <stdio.h>
#include "../include/vertex.h"

void vertex_print(const void *v) {
    printf("%d(%d)", vertex_data(v), vertex_weight(v));
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