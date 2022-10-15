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
    printf("counter: %d\n", counter);
    return 0;
    
}

char *parse_stdinn(char *str) {
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ') str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    printf("string: %s\n", str);
    return str;
    
}
int main(int argc, char *argv[]) {

    parse_stdin();
    char text[MAX_RECORD_LEN] = "ah oj";
    parse_stdinn(text);

    if (argc > 2) {
        printf("Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }


    else if (argc == 2) {
        char *number = argv[1];
        printf("number: %s\n", number);
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