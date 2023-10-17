#include "stdlib.h"
#include "../include/graph.h"
// #include "../include/print_graph.h"

int main() {
    Graph graph;
    char *path = "data/graph-test-100.txt";

    graph_build(&graph, path);
    
    return 0;
}