#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/list.h"

/// @brief 
/// @param first_key 
/// @param second_key 
/// @return 
int graph_macth(const void *first_key, const void *second_key) {
    if (first_key == NULL || second_key == NULL) 
        return 0;

    if ((int)first_key == (int)second_key)
        return 1;

    return 0;
}

int main() {
    Graph graph;
    char *path = "data/graph-test-100.txt";

    graph_init(&graph, graph_macth, NULL);
    graph_build(&graph, path);

    // for(Cell *element = list_head(graph.adjlists); element != NULL; element = list_next(element)) {
    //     printf("%d: ", (int)(((AdjList *) list_data(element))->vertex));

    //     for(Cell *i = list_head(&((AdjList *) list_data(element))->adjacent); i != NULL; i = list_next(i))
    //         printf("%d -", (int)(i->data));
    //     printf("\n");
    // }

    return 0;
}