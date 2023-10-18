#include <stdlib.h>
#include "../include/list.h"
#include "../include/graph.h"
#include "../include/dfs.h"

/// @brief 
/// @param graph  
/// @param v 
/// @param table 
/// @param lifetime 
static void dfs(Graph *graph, int v, DfsTable *table, int *lifetime) {
    // list_sort(graph->adjacent[v]);

    table->start[v] = ++*lifetime;

    for(Cell *i = list_head(graph->adjacent[v]); i != NULL; i = list_next(i)) {
        if(table->start[list_data(i)] == 0) {
            table->father[list_data(i)] = v;
            dfs(graph, list_data(i), table, lifetime);
        }
    }
    
    table->end[v] = ++*lifetime;
}

void dfs_table_free(DfsTable *table) {
    free(table->start);
    free(table->end);
    free(table->father);
}

void dfs_table_init(DfsTable *table, int n) {
    table->start = (int *) malloc(sizeof(int) * n);
    table->end = (int *) malloc(sizeof(int) * n);
    table->father = (int *) malloc(sizeof(int) * n);

    for(int i = 1; i < n; i++) {
        table->start[i] = 0;
        table->end[i] = 0;
        table->father[i] = -1;
    }
}

void graph_dfs(Graph *graph, DfsTable *table) {
    int n = graph->vcount + 1, lifetime = 0;
    
    dfs_table_init(table, n);
    dfs(graph, 1, table, &lifetime);
}