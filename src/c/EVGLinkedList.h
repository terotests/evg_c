
#ifndef EVG_LINKED_LIST_H_INCLUDED
#define EVG_LINKED_LIST_H_INCLUDED


typedef struct LinkedListNode {
    char *name;
    void *data;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct LinkedList {
    struct LinkedListNode * tail;
} LinkedList;

LinkedList *createList();

void List_push( LinkedList *list, LinkedListNode * node );

LinkedListNode *List_pop( LinkedList *list );
LinkedListNode *List_find( LinkedList *list, char *name );
LinkedListNode *ListNode_Create( char *name, void *data );



#endif
