#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
// #include "../include/graph.h"
#include "../include/list.h"
// #include "../include/print_graph.h"

/// @brief 
/// @param first_key 
/// @param second_key 
/// @return 
int macth(const void *first_key, const void *second_key) {
    if (first_key == NULL || second_key == NULL) 
        return 0;
    printf("MACTH 0\n");

    if (!memcmp(first_key, second_key, sizeof(int)))
        return 1;
    printf("MACTH 1\n");
    return 0;
}

/// @brief 
/// @param data 
void destroy(void *data) {
    free(data);
}

int main() {
    List list;
    
    list_init(&list, sizeof(int), destroy);
    printf("list init \n");
    
    for (int i = 1; i < 11; i++) {
        if (!list_insert(&list, NULL, (void *)&i))
            printf("insert list: %d\n", i);
        else 
            printf("error insert list\n");
    }

    for (int i = 0; i < 3; i++) {
        if (!list_remove(&list, NULL))
            printf("remove list: %d\n", i);
        else 
            printf("error insert list\n");
    }

    for (Cell *i = list_head(&list); i != NULL; i = list_next(i))
        printf("%d - ", *(int *)list_data(i));
    printf("\n");

    int x = 6;
    Cell *cell = list_search(&list, (void *) &x);

    if (cell != NULL)
        printf("Cell: %d\n", *(int *) list_data(cell));

    list_destroy(&list);

    return 0;
}