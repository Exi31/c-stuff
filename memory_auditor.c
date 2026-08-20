
#include <stdio.h>

void audit_memory(const void *addr, size_t total_bytes, char type_flag) {
    const char *addr1 = (const char *) addr;
    const int *addr2 = (const int *) addr;
    const unsigned char *addr3 = (const unsigned char *) addr;

    switch (type_flag) {
        case 'c': {
            for (size_t i = 0; i < total_bytes; i++) {
                printf("%c (address: %p)\n", *(addr1 + i), addr1 + i);
            }

            printf("\n");
            break;
        }

        case 'i': {
            for (size_t i = 0; i < total_bytes; i++) {
                printf("%d (address: %p)\n", *(addr2 + i), addr2 + i);
            }

            printf("\n");
            break;
        }

        case 'x': {
            for (size_t i = 0; i < total_bytes; i++) {
                printf("%#x (address: %p)\n", *(addr3 + i), addr3 + i);
            }

            printf("\n");
            break;
        }
    }
}

int main(void) {
    const char greeting[] = "Hack";
    int secret_keys[] = {0x11223344, 0x55667788};

    audit_memory(greeting, sizeof(greeting), 'c');
    audit_memory(secret_keys, sizeof(secret_keys), 'i');
    audit_memory(secret_keys, sizeof(secret_keys), 'x');

    return 0;
}