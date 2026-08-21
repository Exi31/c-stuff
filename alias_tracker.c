
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int target = 1337;
    int *alias_A = &target;
    int *alias_B = alias_A;

    printf("%d (%p)\n", target, &target);
    printf("%d (%p)\n", *alias_A, alias_A);
    printf("%d (%p)\n", *alias_B, alias_B);

    *alias_A = 999;
    printf("%d (%p)\n", target, &target);
    printf("%d (%p)\n", *alias_A, alias_A);
    printf("%d (%p)\n", *alias_B, alias_B);

    int *master_ptr = malloc(sizeof(int));
    if (master_ptr == NULL) {
        printf("Allocation failed\n");
        return -1;
    }
    *master_ptr = 5555;

    int *alias_ptr = master_ptr;
    
    // Convert the pointer addresses to raw unsigned long integers
    // This breaks the compiler's "pointer-use-after-free" tracking chain!
    unsigned long master_addr_val = (unsigned long)master_ptr;
    unsigned long alias_addr_val  = (unsigned long)alias_ptr;

    printf("master_ptr address: %p\n", master_ptr);
    printf("alias_ptr address: %p\n", alias_ptr);

    free(master_ptr);
    master_ptr = NULL;

    // Update our integer holder for master_ptr to reflect the NULL swap
    master_addr_val = (unsigned long)master_ptr;

    // Now we print the raw numeric address values instead of the pointer types!
    printf("master_ptr address: 0x%lx\n", master_addr_val);
    printf("alias_ptr address: 0x%lx\n", alias_addr_val);

    return 0;
}