/* A linked list node containing generic data. */
typedef struct LinkedListNode {
   void *data;
   struct LinkedListNode *next;
} LinkedListNode;

/* Linked List struct */
typedef struct {
    LinkedListNode *head;
    int size;
} LinkedList;

/* Linked list functions */
LinkedList *MakeLinkedList();
short PushLinkedList(LinkedList *list, void *data);
void FreeLinkedList(LinkedList *list);