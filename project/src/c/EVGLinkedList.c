#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "EVGLinkedList.h"

LinkedList *createList() {
    LinkedList *newList = malloc(sizeof(LinkedList));
    newList->tail = NULL;
    return newList;
}

void List_push( LinkedList *list, LinkedListNode * node ) {
    node->prev = list->tail;
    list->tail = node;
}

LinkedListNode *List_pop( LinkedList *list ) {
    LinkedListNode * node = list->tail;
    // free( list->tail );
    list->tail = list->tail->prev;
    return node;
}

LinkedListNode *List_find( LinkedList *list, char *name ) {
    LinkedListNode * node = list->tail;
    while(node) {
        if(node->name) {
            if(strcmp(node->name, name)==0) return node;
        }
        node = node->prev;
    }
    return NULL;
}

// there could be different kind of lists...
LinkedListNode *ListNode_Create( char *name, void *data ) {
    LinkedListNode *newItem = malloc(sizeof(LinkedListNode));
    newItem->name = name;
    newItem->data = data;
    return newItem;
}



