/* Linked list functions implementation 
 * Joseph Michaels
 * Feb. 2009
 */

#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

/* Construct a linked list node and initialize it
 * Returns      A pointer to the constructed linked list node.
 */
LinkedListNode *MakeLinkedListNode(void *data, LinkedListNode *next) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->data = data;
    node->next = next;
    return node;
}

/* Construct a linked list and initialize it
 * Returns      A pointer to the constructed linked list.
 */
LinkedList *MakeLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/* Find if data already exists in a linked list
 * Parameters
 *      LinkedList *list    The linked list to search through
 *      void *data          The data to look for
 * Returns
 *      short           1 if the data exists, 0 if not
 */
short FindInLinkedList(LinkedList *list, void *data) {
    LinkedListNode *node = list->head;
    while (node != NULL) {
        /*printf("%d==%d; ", node->data, data);*/
        if (node->data == data) {
            return 1;
        }
        node = node->next;
    }
    /* Nothing found */
    return 0;
}

/* Push an element to the front of the linked list
 * Parameters
 *      LinkedList *list    The linked list
 *      void *data          The data to push
 * Returns
 *      short          0 always (will be changed to success/failure in future)
 */
short PushLinkedList(LinkedList *list, void *data) {
    if (!FindInLinkedList(list, data)) {
        if (list->head) {
            LinkedListNode *temp = list->head;
            list->head = MakeLinkedListNode(data, temp);
            list->size++;
        } else {
            list->head = MakeLinkedListNode(data, NULL);
            list->size++;
        }
    }
    return 0;
}

/* Look at the first element in the linked list
 * Parameters
 *      LinkedList *list    The linked list
 * Returns
 *      void *      The first element of the linked list
 */
void *PeekLinkedList(LinkedList *list) {
    if (list->head) {
        return list->head->data;
    } else {
        return NULL;
    }
}

/* Recursively free the memory for a linked list node and all the following elements
 * Data is NOT freed.
 */
void FreeLinkedListNode(LinkedListNode *node) {
    if (node != NULL) {
        FreeLinkedListNode(node->next);
        free(node);
    }
}

/* Free the linked list struct and all its nodes */
void FreeLinkedList(LinkedList *list) {
    if (list != NULL) {
        FreeLinkedListNode(list->head);
        free(list);
    }
}