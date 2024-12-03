#include <stdio.h>
#include <stdlib.h>

// Do insertion sort to sort while reading values
void insertionSort(int *array, int value, int num_lines) {
    int i = num_lines - 1;
    while (i >= 0 && array[i] > value) {
        array[i + 1] = array[i];
        i--;
    }
    array[i + 1] = value;
}

// Read file and insertion sort integers into two arrays
// Allocate initial capacity and double if capacity is exceeded
int readIntegers(const char *filename, int **array1, int **array2) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("could not open file");
        return -1;
    }

    int capacity = 10;
    *array1 = (int *)malloc(capacity * sizeof(int));
    *array2 = (int *)malloc(capacity * sizeof(int));

    int num_lines = 0;
    int num1, num2;
    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        // If we have exceeded the capacity of the array then realloc, double the size
        if (num_lines >= capacity) {
            capacity *= 2;
            *array1 = (int *)realloc(*array1, capacity * sizeof(int));
            *array2 = (int *)realloc(*array2, capacity * sizeof(int));
        }

        insertionSort(*array1, num1, num_lines);
        insertionSort(*array2, num2, num_lines);
        num_lines++;
    }

    fclose(file);
    return num_lines;
}

// Calculate the total similarity score
int calculateSimilarityScore(int *array1, int *array2, int count) {
    int total_similarity = 0;

    // For each element in array1, count how many times it appears in array2
    for (int i = 0; i < count; i++) {
        int num1 = array1[i];
        int count_in_array2 = 0;

        // Count the occurrences of num1 in array2
        for (int j = 0; j < count; j++) {
            if (array2[j] == num1) {
                count_in_array2++;
            }
        }

        // Add the similarity score (num1 * occurrences in array2)
        total_similarity += num1 * count_in_array2;
    }

    return total_similarity;
}

int main() {
    const char *filename = "../inp.txt";
    int *array1 = NULL, *array2 = NULL;

    int count = readIntegers(filename, &array1, &array2);
    if (count > 0) {
        // Calculate the total similarity score
        int total_similarity = calculateSimilarityScore(array1, array2, count);

        // Free the allocated memory
        free(array1);
        free(array2);

        // Print the total similarity score
        printf("Total similarity score: %d\n", total_similarity);
    } else {
        perror("could not read and sort file");
        return -1;
    }

    return 0;
}
