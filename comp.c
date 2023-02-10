#include <stdio.h>
#include <stdlib.h>

char *fileopen(char path[]){
    long length;
    char *buffer = 0;
    FILE *f;
    f = fopen(path, "r");
    if (f){
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer){
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }
    return buffer;
}

void comp(char path_a[], char path_b[]){
    char *con_a = fileopen(path_a);
    char *con_b = fileopen(path_b);
    int choice;
    
    printf("Do you want to show first or second file (1/2): ");
    scanf("%i", &choice);

    if (choice == 1){
        for (int i=0; i < (sizeof con_a / sizeof *con_a); i++){
            if (con_a[i] == con_b[i]){
                printf("%c", con_a[i]);
            }
            else{
                printf("\x1b[31m%c\x1b[0m", con_a[i]);
            }
        }
    }
    else if (choice == 2){
        for (int i = 0; i < (sizeof con_b / sizeof *con_b); i++){
            if (con_b[i] == con_a[i]){
                printf("%c", con_b[i]);
            }
            else{
                printf("\x1b[31m%c\x1b[0m", con_b[i]);
            }
        }
    }
    else{
        comp(path_a, path_b);
    }
}

int main(int argc, char *argv[]){
    if (argc < 3 || argv[1] == "-h" || argv[1] == "--help"){
        printf("Usage: comp <path of first file> <path of second file>\n");
    }
    else if (argv[1] != "" && argv[2] != ""){
        comp(argv[1], argv[2]);
        return 0;
    }
}
