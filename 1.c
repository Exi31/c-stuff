
// Write a C program (buffer_hijack.c) where you have two adjacent character buffers on the stack. Your goal is to overflow the first buffer (input) to completely overwrite the contents of the second buffer (target) so that it changes from "SECURE" to "PWNED".
// When you print target at the end, it must output exactly "PWNED" with no trailing garbage or memory leaks.

// compile the code with -fno-stack-protector to allow stack overflowing stuff

#include <stdio.h>

int main(void) {
    char target[8] = "SECURE";
    char input[8];

    printf("Starting address of input string: %p\n", input);
    printf("Starting address of target string: %p\n", target);
    printf("Initial value of target: %s\n", target);

    for (int i = 0; i < 14; i++) {
        int modulo = i % 6;
        
        switch (modulo) {
            case 0: { 
                input[i] = 'D';
                break; 
            }

            case 1: { 
                input[i] = '\0';
                break; 
            }

            case 2: { 
                input[i] = 'P';
                break; 
            }

            case 3: { 
                input[i] = 'W';
                break; 
            }

            case 4: { 
                input[i] = 'N';
                break; 
            }

            case 5: { 
                input[i] = 'E';
                break; 
            }
        }
    }

    printf("Target value now: %s\n", target);

    return 0;
}