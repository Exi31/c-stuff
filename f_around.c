
#include <stdio.h>

int main(void) {
    long long arr1[] = {1, 2, 3, 4, 9, 10};
    short arr2[] = {5, 6, 7, 8, 11, 12};

    long long *ptr1 = arr1;
    short *ptr2 = arr2 + 1;

    long long *shifted_ptr1 = ptr1 + 3;
    short *shifted_ptr2 = ptr2 + 3;

    printf("ptr1 address: %p\n", (void*) ptr1);
    printf("shifted_ptr1 address: %p\n", (void*) shifted_ptr1);
    printf("Difference between shifted_ptr1 and ptr1: %ld byte(s)\n\n", (char*) shifted_ptr1 - (char*) ptr1);

    printf("ptr2 address: %p\n", (void*) ptr2);
    printf("shifted_ptr2 address: %p\n", (void*) shifted_ptr2);
    printf("Difference between shifted_ptr2 and ptr2: %ld byte(s)\n\n", (char*) shifted_ptr2 - (char*) ptr2);

    return 0;
}