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

    // read file into buffer
    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';  // eof

    fclose(file);
    return content;
}

// extract and execute mul , handle do() don't()
int extractMulExpressions(const char *content) {
    int total = 0;
    int i = 0;
    int multiplications_enabled = 1;

    while (content[i] != '\0') {
        // do()
        if (content[i] == 'd' && content[i + 1] == 'o' && content[i + 2] == '(' && content[i + 3] == ')') {
            multiplications_enabled = 1;
            i += 4;  // skip do()
        }
        // don't()
        else if (content[i] == 'd' && content[i + 1] == 'o' && content[i + 2] == 'n' && content[i + 3] == '\'' && content[i + 4] == 't' && content[i + 5] == '(' && content[i + 6] == ')') {

            multiplications_enabled = 0;
            i += 6;  // skip don't()
        }
        else if (content[i] == 'm' && content[i + 1] == 'u' && content[i + 2] == 'l' && content[i + 3] == '(') {
            // skip mul(
            i += 4;

            // get x
            int x = 0;
            while (isdigit(content[i])) {
                x = x * 10 + (content[i] - '0');
                i++;
            }

            // expect comma
            if (content[i] != ',') {
                i++;
                continue;
            }
            i++;  // skip comma

            // get y
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

            if (multiplications_enabled) {
                total += x * y;
            }
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
