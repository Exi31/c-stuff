
// structs & padding in-depth

#include <stdio.h>

struct Target {
    char a;
    short b;
    int c;
};

int main(void) {
    struct Target tar1;

    tar1.a = 0x11;
    tar1.b = 0x2222;
    tar1.c = 0x33333333;

    printf("Size of struct Target: %zu\n", sizeof(struct Target));

    unsigned char *byte_ptr = (unsigned char*) &tar1;

    for (size_t i = 0; i < sizeof(struct Target); i++) {
        printf("\nMemory address of the byte: %p\n", (byte_ptr + i));
        printf("Byte index: %zu\n", i);
        printf("Hex value stored at this byte: %x\n", *(byte_ptr + i));
    }

    return 0;
}