#include <stdlib.h>
#include <stdio.h>
#include "array.h"

/* Construct an array
 * Returns
 *      Array *     A pointer to the constructed array.
 */
Array *MakeArray()
{
    Array *array = malloc(sizeof(Array));
    array->size = 0;
    array->_mem_sz = 1;
    array->data = malloc(sizeof(void *));
    return array;
}

/* Add an element to the array */
short AddToArray(Array *array, void *data)
{
    array->size++;
    if (array->size > array->_mem_sz) {
        /* Double the size. */
        array->_mem_sz = array->_mem_sz * 2;
        array->data = realloc(array->data, sizeof(void *) * array->_mem_sz);
    }
    
    array->data[array->size-1] = data;
    return 1;
}

/* Add an element to the array if it isn't already in the array. */
short AddUniqueToArray(Array *array, void *data)
{
    if (array != NULL) {
        /* Make sure the pointer is not already in the array. */
        if (!ExistsInArray(array, data)) {
            return AddToArray(array, data);
        }
    }
    return 0;
}

/* Find if there exists an element that points to some arbitrary data */
short ExistsInArray(Array *array, void *data)
{
    int i;
    for (i=0; i<array->size; i++) {
        if (data == array->data[i]) {
            return 1;
        }
    }
    return 0;
}

/* Get the element at the specified index. */
void *GetInArray(Array *array, int index)
{
    if ((array != NULL) && (index < array->size)) {
        return array->data[index];
    } else {
        return NULL;
    }
}

/* Remove an element from the array. Does not deallocate.
 * Parameters
 *      Array *array        The array to remove from
 *      void *data          The arbitrary pointer to find and remove
 * Returns
 *      void
 */
void RemoveFromArray(Array *array, void *data)
{
    int i;
    for (i=0; i<array->size; i++) {
        if (data == array->data[i]) {
            int j;
            /* Shift everything to the left */
            for (j=i; j+1 < array->size; j++) {
                array->data[j] = array->data[j+1];
            }
            array->size--;
            break;
        }
    }
}

/* Print an array */
void PrintArray(Array *array)
{
	char s[600];
    if (array != NULL) {
        int i;
        for (i=0; i<array->size; i++) {
			//char sadd[40];
			sprintf(s, "%s", GetInArray(array, i));
			//strcat(s, sadd);
        }
        sprintf(s, "\n");
    }
}

/* Deallocate an array */
void DestroyArray(Array *array)
{
    if (array != NULL) {
        if (array->data != NULL) {
            free(array->data);
        }
        free(array);
    }
}

/* Deallocate an array and all of the elements in it. */
void DestroyArrayAndData(Array *array)
{
    int i;
    for (i=0; i<array->size; i++) {
        free(GetInArray(array, i));
    }
    DestroyArray(array);
}