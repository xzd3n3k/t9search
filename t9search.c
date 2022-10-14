#include <stdio.h>
#include <string.h>
#define MAX_RECORD_LEN 100

int parse_stdin() {
    char line[MAX_RECORD_LEN];
    int counter = 0;

    while (fgets(line, MAX_RECORD_LEN+1, stdin))
    {
        counter += 1;
    }
    printf("%d", counter);
    return 0;
    
}
int main(int argc, char *argv[]) {

    parse_stdin();
    if (argc > 2) {
        printf("Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }


    else if (argc == 2) {
        char *number = argv[1];
        printf("%s\n", number);
        printf("%lu", strlen(number));
    }


    else {

        char line[MAX_RECORD_LEN];
        int switcher = 0;

        while (fgets(line, MAX_RECORD_LEN+1, stdin)) {
            
            for (int i = 0; i < MAX_RECORD_LEN+1; i++) {
                if (line[i] == '\n') {line[i] = '\0';}
            }

            switch (switcher)
            {
            case 0:
                printf("%s, ", line);
                switcher = 1;
                break;

            case 1:
                printf("%s\n", line);
                switcher = 0;
                break;

            }
        }
        
    }
    
    
    return 0;
}