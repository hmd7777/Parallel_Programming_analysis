#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *arr, int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}
int* create_random_array(int size) {
    // Seed the random number generator
    srand(time(NULL));

    // Dynamically allocate memory for the array
    int* array = malloc(size * sizeof(int));
    if (array == NULL) {
        // In case memory allocation fails
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Fill the array with random numbers between 0 and 5
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 6; // rand() % 6 generates a number in the range 0-5
    }

    return array;
}
// Function to count the occurrences of 1 in an array
int true_count_ones(const int* array, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == 1) {
            count++;
        }
    }
    return count;
}
// Example usage
/*
int main() {
    for (int size = 1000; size <= 1000000000; size *= 1000) {
        int* myArray = create_random_array(size);
    if (myArray == NULL) {
        printf("%d is too large\n", size);
        break;
        // Handle the error as needed
    }
        clock_t start = clock();

        // Function whose execution time is to be measured
        int count = count_ones(myArray, size);

        // End timing
        clock_t end = clock();

        // Calculate the time taken in seconds
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Time taken to initialize the array of size %d: %f seconds\n", size, time_taken);

        // Free the memory allocated for myArray
        free(myArray);
    }


    return 0;
}
*/