
#include "algorithms.h"




void fromArray(linked_list_t* ll, int *arr, size_t size)
{
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        ll->push_front(ll, arr[i]);
    } while(i--!=0);
}

int* toArray(const linked_list_t* ll)
{
    int leng = ll->length(ll);
    int *values = (int*) malloc(leng*sizeof(int));
    while (head) {
        values[--leng] = head->value;
        head = head->next;
    }
    return values;
}  



void to_string(const linked_list_t* ll, char* string) 
{
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}