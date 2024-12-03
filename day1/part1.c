// aoc 1

#include <stdio.h>
#include <stdlib.h>

// do insertion sort to sort while reading values
void insertionSort(int *array, int value, int num_lines) {
    int i = num_lines - 1;
    while (i >= 0 && array[i] > value) {
        array[i + 1] = array[i];
        i--;
    }
    array[i + 1] = value;
}

// read file and insertion sort integers into two arrays
// alloc an initial capacity and double if capacity is exceeded
int readAndSortIntegers(const char *filename, int **array1, int **array2) {
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
        // if we have exceeded the capacity of the array then realloc, double the size
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

// distance between two numbers is just abs
int calculateDistance(int n1, int n2) {
    return abs(n1-n2);
}

int main() {
    const char *filename = "../inp.txt";
    int *array1 = NULL, *array2 = NULL;

    int count = readAndSortIntegers(filename, &array1, &array2);
    if (count > 0) {
        // the arrays have been sorted
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += calculateDistance(array1[i], array2[i]);
        }
        free(array1);
        free(array2);
        printf("total : %d", total);
    } else {
        perror("could not read and sort file");
        return -1;
    }

    return 0;
}
