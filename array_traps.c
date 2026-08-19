
#include <stdio.h>

int main(void) {
    int *ptr_array[3];
    int (*array_ptr)[3] = NULL;
    int raw_array[] = {10, 20, 30};

    array_ptr = &raw_array;
    ptr_array[0] = raw_array;
    ptr_array[1] = raw_array + 1;
    ptr_array[2] = raw_array + 2;

    printf("sizeof(ptr_array) = %zu\n", sizeof(ptr_array));
    printf("sizeof(array_ptr) = %zu\n", sizeof(array_ptr));
    printf("sizeof(*array_ptr) = %zu\n", sizeof(*array_ptr));

    printf("2nd element of raw_array: %d\n", (*array_ptr)[1]);
    printf("3rd element of raw_array: %d\n", *(ptr_array[2]));

    return 0;
}