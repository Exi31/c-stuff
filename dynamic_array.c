
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = NULL;
    size_t capacity = 2, count = 0;

    numbers = malloc(capacity * sizeof *numbers);
    if (numbers == NULL) {
        printf("Allocation failed.\n");
        return 1;
    }

    printf("Original address of the heap part we borrowed: %p\n", numbers);

    for (int i = 1; i <= 5; i++) {
        if (count == capacity) {
            capacity *= 2;
            int *temp = realloc(numbers, capacity * sizeof *numbers);

            if (temp == NULL) {
                printf("Reallocation failed.\n");
                free(numbers);
                numbers = NULL;

                return 1;
            }

            numbers = temp;
            printf("[GROWTH] Resized array to capacity %zu at address %p\n", capacity, numbers);
        }

            *(numbers + i - 1) = i * 10;
            count++;
        }
    

    printf("Elements in the array:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d (index: %d)\n", *(numbers + i), i);
    }

    free(numbers);
    numbers = NULL;

    return 0;
}