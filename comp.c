#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fileopen(char path[]) {
    long length;
    char *buffer = NULL;
    FILE *f;
    f = fopen(path, "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if (buffer) {
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
        }
        fclose(f);
    }
    return buffer;
}

void comp(char path_a[], char path_b[]) {
    char *con_a = fileopen(path_a);
    char *con_b = fileopen(path_b);
    int choice;
    size_t len_a, len_b;
    
    if (con_a == NULL || con_b == NULL) {
        printf("Error: failed to open files\n");
        exit(EXIT_FAILURE);
    }
    
    len_a = strlen(con_a);
    len_b = strlen(con_b);

    printf("Do you want to show first or second file (1/2): ");
    scanf("%i", &choice);

    if (choice == 1) {
        for (size_t i = 0; i < len_a && i < len_b; i++) {
            if (con_a[i] == con_b[i]) {
                printf("%c", con_a[i]);
            }
            else {
                printf("\x1b[31m%c\x1b[0m", con_a[i]);
            }
        }
    }
    else if (choice == 2) {
        for (size_t i = 0; i < len_a && i < len_b; i++) {
            if (con_b[i] == con_a[i]) {
                printf("%c", con_b[i]);
            }
            else {
                printf("\x1b[31m%c\x1b[0m", con_b[i]);
            }
        }
    }
    else {
        comp(path_a, path_b);
    }

    free(con_a);
    free(con_b);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: comp <path of first file> <path of second file>\n");
        return 0;
    }
    else if (strlen(argv[1]) > 0 && strlen(argv[2]) > 0) {
        comp(argv[1], argv[2]);
        return 0;
    }
}

