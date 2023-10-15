#include "stdlib.h"
#include "../include/graph.h"
#include "../include/print_graph.h"

int main() {
    Graph graph;
    table table;
    char *path = "data/graph-test-100.txt";

    build_graph(&graph, path);
    table = dfs(graph);
    print_edge_classification(8, graph, table);

    return 0;
}