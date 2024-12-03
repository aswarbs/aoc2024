#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSafe(int nums[], int count) {
    int is_increasing = 1, is_decreasing = 1, is_safe = 1;
    for (int i = 0; i < count - 1; i++) {
        if (nums[i] >= nums[i + 1]) {
            is_increasing = 0;
        }
        if (nums[i] <= nums[i + 1]) {
            is_decreasing = 0;
        }
        int diff = abs(nums[i] - nums[i + 1]);
        if (diff < 1 || diff > 3) {
            is_safe = 0;
        }
    }
    return (is_increasing || is_decreasing) && is_safe;
}

int readAndCheckSafe(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("could not open file");
        return -1;
    }

    int safe_count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        int nums[100];
        int count = 0;

        // Tokenize the line into numbers
        char *token = strtok(line, " ");
        while (token != NULL) {
            nums[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // is original sequence safe
        if (isSafe(nums, count)) {
            safe_count++;
            continue;
        }

        // is removing one level safe
        int can_be_safe = 0;
        for (int i = 0; i < count; i++) {
            int temp_nums[100];
            int temp_count = 0;

            for (int j = 0; j < count; j++) {
                if (i != j) {
                    temp_nums[temp_count++] = nums[j];
                }
            }

            if (isSafe(temp_nums, temp_count)) {
                can_be_safe = 1;
                break;
            }
        }

        if (can_be_safe) {
            safe_count++;
        }
    }

    fclose(file);
    return safe_count;
}

int main() {
    const char *filename = "../inp.txt";

    int safe_count = readAndCheckSafe(filename);
    if (safe_count > 0) {
        printf("safe count: %d\n", safe_count);
    } else {
        perror("could not read and check file");
        return -1;
    }

    return 0;
}
