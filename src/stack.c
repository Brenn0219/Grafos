#include <stdlib.h>
#include "../include/list.h"
#include "../include/stack.h"

int stack_push(Stack *stack, const void *data) {
    return list_insert(stack, NULL, data);
}

int stack_pop(Stack *stack) {
    return list_remove(stack, NULL);
}

int stack_search(Stack *stack, const void *data) {
    for (Cell *element = list_head(stack); element != NULL; element = list_next(element)) {
        if (stack->match(data, list_data(element)))
            return 1;
    }

    return 0;
}