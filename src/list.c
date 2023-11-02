#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../include/list.h"

void list_init(List *list, size_t structure_size, void (* destroy) (void *data)) {
    list->size = 0;
    list->structure_size = structure_size;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(List *list) {
    void *data;

    while (list_size(list) > 0) {
        if (list_remove(list, NULL) == -1)
            return;
    }

    memset(list, 0, sizeof(List));
}

Cell* list_new_cell(const void *data, size_t structure_size) {
    Cell *new_cell = (Cell *) malloc(sizeof(Cell));
    
    if (new_cell == NULL)
        return NULL;    
    
    new_cell->next = NULL;
    new_cell->data = (void *) malloc(structure_size); 
    memcpy(new_cell->data, data, structure_size);
    
    return new_cell;   
}

int list_insert(List *list, Cell *element, const void *data) {
    Cell *new_element = list_new_cell(data, list_structure_size(list));
    
    if (new_element == NULL)
        return -1;
    
    if (element == NULL) {
        if (list_size(list) == 0) 
            list->tail = new_element;
        
        new_element->next = list->head;
        list->head = new_element;
    } else {
        if (element->next == NULL)
            list->tail = new_element;
        
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    
    return 0;
}

int list_remove(List *list, Cell *element) {
    Cell *old_element;

    if (list_size(list) == 0)
        return -1;
    
    if (element == NULL) {
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) 
            list->tail = NULL;
    } else {
        if (element->next == NULL)
            return -1;

        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL)  
            list->tail = element;
    }

    if (list->destroy != NULL)
        list->destroy(old_element->data); 

    free(old_element);
    list->size--;

    return 0;
}