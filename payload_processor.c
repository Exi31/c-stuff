
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. Declare your typedef for 'transform_fn' here
/* YOUR CODE HERE */
typedef void (*transform_fn)(char *);

// 2. Implement your three transformation functions here
void op_xor(char *data) {
    /* YOUR CODE HERE */
    int i = 0;

    while (data[i] != '\0') {
        data[i] ^= 0x5A;
        i++;
    }
}

void op_reverse(char *data) {
    /* YOUR CODE HERE */
    int length = 0;

    while (data[length] != '\0') {
        length += 1;
    }

    for (int i = 0; i < length / 2; i++) {
        char temp = data[i];
        data[i] = data[length - i - 1];
        data[length - i - 1] = temp;
    }
}

void op_invert(char *data) {
    /* YOUR CODE HERE */
    int i = 0;

    while (data[i] != '\0') {
        if (data[i] >= 0x41 && data[i] <= 0x5A) {
            data[i] += 0x20;
        } else if (data[i] >= 0x61 && data[i] <= 0x7A) {
            data[i] -= 0x20;
        }

        i++;
    }
}


// 3. Implement the dispatcher
void dispatch_transform(int command_id, char *payload) {
    // Declare the table of size 3 using your preferred spaced-bracket style
    /* YOUR CODE HERE: Declare and initialize dispatch_table[ 3 ] */
    transform_fn dispatch_table[ 3 ] = {op_xor, op_reverse, op_invert};

    // Implement a strict, secure bounds check
    /* YOUR CODE HERE: Perform bounds checking and execute the handler */
    if (command_id >= 0 && command_id <= 2) {
        dispatch_table[command_id](payload);
    } else {
        printf("ERROR\n");
    }
}

int main(void) {
    // Test Case 1: XOR (Expected output: Raw XORed bytes)
    char msg1[ 16 ] = "SYSTEMS_MASTER";
    printf("Original 1: %s\n", msg1);
    dispatch_transform(0, msg1);
    printf("XORed:      %s\n", msg1);
    dispatch_transform(0, msg1); // XORing again restores the original
    printf("Restored:   %s\n\n", msg1);

    // Test Case 2: Reverse (Expected output: RETSAM_SMETSYS)
    char msg2[ 16 ] = "SYSTEMS_MASTER";
    printf("Original 2: %s\n", msg2);
    dispatch_transform(1, msg2);
    printf("Reversed:   %s\n\n", msg2);

    // Test Case 3: Invert Case (Expected output: sYSTEMs_mASTER)
    char msg3[ 16 ] = "Systems_Master";
    printf("Original 3: %s\n", msg3);
    dispatch_transform(2, msg3);
    printf("Inverted:   %s\n\n", msg3);

    // Test Case 4: Attack Attempt (Expected: Clean error message, no crash)
    printf("Triggering OOB Attack Index...\n");
    dispatch_transform(99, msg3); 

    return 0;
}