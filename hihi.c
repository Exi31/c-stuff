
// 📡 GitHub Challenge: "The Beacon Metadata Validator" (Created by Google Notebook)

// 🎯 The Objective
// Write a single-file C program (beacon.c) that defines a contiguous stack array of "beacons" (integers) and programmatically proves to the user how the compiler handles array metadata differently depending on whether it is inside the original scope or inside a helper function.

// 🛠️ Requirements & Specifications
// Array Declaration: In main(), declare a contiguous stack-allocated array of exactly 6 integers representing beacon IDs (e.g., 0x100, 0x200, etc.)

// Compile-Time Size Auditing: In main(), print:
// - The total size of your beacon array in bytes using sizeof
// - The size of a pointer variable pointing to that array
// - The mathematically calculated number of elements in the array using only the sizeof operator (do not hardcode the number 6).

// The Decay Inspection Function: Write a function with the following signature: void verify_beacons(int *beacons, size_t count)

// Loss of Metadata Verification: Inside verify_beacons:
// - Print the sizeof of your beacons parameter to prove that the array has decayed to a pointer and its original size metadata has been lost
// - Use a loop to print each beacon's index, hex value, and its exact virtual memory address

// Execution and Calling: In main(), call verify_beacons by passing your stack array

// Compilation Hygiene: You must compile this program using strict flags to ensure zero errors and zero warnings

#include <stdio.h>
#include <stdlib.h>

void verify_beacons(int *beacons, size_t count) {
    printf("Size of the beacons param: %zu byte(s)\n", sizeof(beacons));
    for (size_t i = 0; i < count; i++) {
        printf("Index %zu | %#x | %p\n", i, *(beacons + i), (beacons + i));
    }
}

int main(void) {
    int beacon_ids[] = {0x100, 0x200, 0x300, 0x400, 0x500, 0x600};

    printf("Beacon array size: %zu byte(s)\n", sizeof(beacon_ids));
    printf("Size of the pointer pointing to the array: %zu byte(s)\n", sizeof(&beacon_ids));

    int count = sizeof(beacon_ids) / sizeof(int);
    printf("Number of elements inside the array: %d\n", count);

    verify_beacons(beacon_ids, count);

    return 0;
}