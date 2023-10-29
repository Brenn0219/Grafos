#include <stdlib.h>
#include "../include/list.h"
#include "../include/stack.h"

int stack_push(Stack *stack, const void *data) {
    return list_insert(stack, NULL, data);
}

int stack_pop(Stack *stack) {
    return list_remove(stack, NULL);
}