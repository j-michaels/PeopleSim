/* Immutable arrays are so 20th century. */
typedef struct {
    void **data;
    int size, _mem_sz;
} Array;

typedef struct {
    Array *array;
    int currentIndex;
} ArrayIterator;

Array *MakeArray();
short AddToArray(Array *array, void *data);
short AddUniqueToArray(Array *array, void *data);
short ExistsInArray(Array *array, void *data);
void *GetInArray(Array *array, int index);
void DestroyArray(Array *array);
void DestroyArrayAndData(Array *array);
void RemoveFromArray(Array *array, void *data);