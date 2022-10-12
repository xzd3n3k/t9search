#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }

    else if (argc == 2) {
        char *number = argv[1];
        printf("%s\n", number);
    }

    else {

        while (1) {
            int character = fgetc(stdin);

            if (character == EOF) break;
            putchar(character);
        }
        
    }
    
    
    return 0;
}