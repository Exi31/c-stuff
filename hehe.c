
// 📡 The MA/VR Double-Agent Challenge: "The Null-Byte Payload Splitter"
// This challenge is designed to push your understanding of the Null Terminator ('\0') to its absolute limit, simulating a real scenario encountered in both Malware Analysis (bypassing naive security scanners) and Vulnerability Research (handling raw binary streams safely).
// You will build this entire C program (payload_splitter.c) completely from scratch.

// 🎯 The Objective
// Develop a C program that demonstrates how standard string functions completely fail when parsing a binary buffer containing an embedded null byte (0x00), and write a robust "Secure Binary Parser" that processes the entire block without getting tripped up by the early stop-sign.

// 🛠️ Requirements & Specifications
// 1. The Raw Payload Buffer: In main(), declare a contiguous stack-allocated char array named payload containing the following sequence of bytes:
// 'M', 'A', 0x00, 'V', 'R', 0x00, 'E', 'X',, 'P' (Hint: Use curly bracket {} initialization so you have exact control over every byte).

// 2. The Naive Scanner Proof (The Failure):
// Print the payload using printf("%s\n", payload).
// Print the calculated length of the payload using the standard C function strlen().
// Goal: Observe how these standard C string utilities are "blind" to everything after the first 0x00 byte.

// 3. The Robust Binary Parser: Write a function with the following signature: void parse_binary_payload(const char *buffer, size_t total_size)

// 4. Inside this function:
// Step through the buffer exactly 1 byte at a time using a loop.
// For every byte, check if it is a printable character (like 'M', 'A', 'V') or a non-printable control byte (like 0x00).
// If it is printable, print the character itself.
// If it is 0x00 (or any other non-printable byte), print its hex representation (\x00).
// Goal: The final output of this function must print: MA\x00VR\x00EXP.

// 5. No Hardcoding: Calculate the total_size of the payload in main() using the sizeof operator. Do not hardcode the number 9.

// 6. Compilation: Ensure the code compiles with zero warnings or errors using strict flags.

// This exercise is highly realistic. Security scanners often miss appended malicious payloads because they scan buffers using standard C-string functions, stopping at the first 0x00 while the operating system's loader executes the whole thing.


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void parse_binary_payload(const char *buffer, size_t total_size) {
    for (int i = 0; i < total_size; i++) {
        if (buffer[i] == '\0') printf("\\x00");             // thêm một dấu \ để bypass cái character sequence
        else printf("%c", buffer[i]);
    }

    printf("\n");
}

int main(void) {
    char payload[] = {'M', 'A', '\0', 'V', 'R', '\0', 'E', 'X', 'P'};

    printf("%s\n", payload);
    printf("Length of the payload (not gonna be correct): %ld\n", strlen(payload));

    printf("Output: ");
    parse_binary_payload(payload, sizeof(payload));        // sizeof() không quan tâm đến '\0'

    return 0;
}
