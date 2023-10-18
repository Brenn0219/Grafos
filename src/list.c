#include <stdlib.h>
#include <memory.h>
#include "../include/list.h"

void list_init(List *list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

int list_remove(List *list, Cell *element) {
    Cell *old_element;

    if(list_size(list) == 0) 
        return -1; 

    // remover o cabecalho
    if(element == NULL) {
        old_element = list->head;
        list->head = list->head->next;

        if(list_size(list) == 1)
            list->tail = NULL;
    } else {
        if(element->next == NULL)
            list->tail = element;
    }

    free(old_element);
    list->size--;

    return 0;
}

int list_destroy(List *list) {
    void *data;

    while (list_size(list) > 0) {
        if (list_remove(list, NULL) != 0)
            return -1;
    } 
    
    memset(list, 0, sizeof(List));
    free(list);

    return 0;
}

int list_insert(List *list, Cell* element, int data) {
    Cell *new_element;

    if((new_element = (Cell *) malloc(sizeof(Cell))) == NULL)
        return -1;
    new_element->data = data;

    if(element == NULL) {  // inserir no topo da lista
        // atualizar o dado final caso a lista esteja vazia
        if(list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    } else { // inserir em algum lugar diferente da cabeça
        // atualizar o dado final caso element seja o antigo dado final
        if (element->next == NULL)
            list->tail = new_element;
        
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    
    return 0;
}

Cell* list_search(List *list, int data) {
    for(Cell *i = list_head(list); i != NULL; i = list_next(i)) {
        if(i->data == data) 
            return i;
    }

    return NULL;
}

void list_sort(List *list) {
    Cell *j, *small;

    for(Cell *i = list_head(list); i->next != NULL ; i = list_next(i)) {
        for(Cell *j = i->next; j != NULL; j = list_next(j)) {
            if (i->data > j->data)
                small = j;
        }

        int temp = i->data;
        i->data = small->data;
        small->data = temp;
    }    
}