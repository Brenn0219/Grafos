#include "stdlib.h"
#include "../include/graph.h"
#include "../include/dfs.h"

int main() {
    Graph graph;
    char *path = "data/graph-test-100.txt";
    DfsTable table;

    graph_build(&graph, path);
    graph_dfs(&graph, &table);
    
    dfs_table_free(&table);
    free(path);
    return 0;
}