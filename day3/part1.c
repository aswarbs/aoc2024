#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char* readFileAsString(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("could not open file");
        return NULL;
    }

    // need the file size to allocate memory for the string
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // allocate memory for string
    char *content = (char *)malloc(fileSize + 1);

    // read file into buff
    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';  // to tell eof

    fclose(file);
    return content;
}

// extract valid mul expressions and execute them and append to total
int extractMulExpressions(const char *content) {
    int total = 0;
    int i = 0;

    while (content[i] != '\0') {
        if (content[i] == 'm' && content[i + 1] == 'u' && content[i + 2] == 'l' && content[i + 3] == '(') {
            // skip mul(
            i += 4;

            // get a
            int x = 0;
            while (isdigit(content[i])) {
                x = x * 10 + (content[i] - '0'); // convert to int with epic '0' find
                i++;
            }

            // expect comma
            if (content[i] != ',') {
                i++;
                continue;
            }
            i++;

            // extract y
            int y = 0;
            while (isdigit(content[i])) {
                y = y * 10 + (content[i] - '0');
                i++;
            }

            // expect )
            if (content[i] != ')') {
                i++;
                continue;
            }
            i++;  // skip )

            total += x * y;
        } else {
            // continue
            i++;
        }
    }

    return total;
}

int main() {
    const char *filename = "../inp.txt";

    char *fileContent = readFileAsString(filename);
    if (fileContent != NULL) {
        int total = extractMulExpressions(fileContent);
        printf("Total: %d\n", total);
        free(fileContent);
    }

    return 0;
}
