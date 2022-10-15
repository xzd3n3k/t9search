#include <stdio.h>
#include <string.h>
#define MAX_RECORD_LEN 100

int count_lines() { // function to count and return how many records do i have from stdin
    char line[MAX_RECORD_LEN];
    int counter = 0;

    while (fgets(line, MAX_RECORD_LEN+1, stdin))
    {
        counter += 1;
    }

    printf("counter: %d\n", counter); //del
    return counter;
    
}

char *rem_spaces(char *str) {   // function to remove spaces from records and return edited records
    int i = 0, j = 0;

    while (str[i])
    {
        if (str[i] != ' ') str[j++] = str[i];
        i++;
    }

    str[j] = '\0';
    return str;
    
}

char *rem_newline(char *str) {   // function to remove newlines from records and return edited records
    int i = 0, j = 0;

    while (str[i])
    {
        if (str[i] != '\n') str[j++] = str[i];
        i++;
    }

    str[j] = '\0';
    return str;
    
}

int len(char *str) {
    int counter = 0;

    for (int i = 0; i < MAX_RECORD_LEN; i++) {
        if (str[i] != '\0' && str[i] != '\n') counter += 1;
    }

    return counter;
}


int main(int argc, char *argv[]) {


    if (argc > 2) { // checking if i have correct number of arguments
        printf("Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }


    else if (argc == 2) {
        char *number = argv[1];

        char line[MAX_RECORD_LEN];
        char number_line[MAX_RECORD_LEN];

        while (fgets(line, MAX_RECORD_LEN+1, stdin))
        {
            /*char *edited_text = rem_spaces(line);
            char *found = strstr(edited_text, number);
            if (found != NULL) {printf("NALEZENO: %s\n", edited_text);}
            printf("edited string: %s\n", edited_text);*/
            char *line_wo_nwl = rem_newline(line);
            char *number_line_wo_nwl = rem_newline(number_line);

            fgets(number_line, MAX_RECORD_LEN+1, stdin);

            char *edited_number = rem_spaces(number_line);
            char *found = strstr(edited_number, number);

            if (found != NULL) {printf("NALEZENO: %s, %s\n", line_wo_nwl, number_line_wo_nwl);}
        }

        return 0;
        
    }


    else { // if no arguments are given, stdout all records

        char line[MAX_RECORD_LEN];
        int switcher = 0; // auxiliary variable to determinate which record belongs to which record

        while (fgets(line, MAX_RECORD_LEN+1, stdin)) {
            
            for (int i = 0; i < MAX_RECORD_LEN+1; i++) {    // iterating each line and checkign where does it end, replacing enter with end symbol
                if (line[i] == '\n') {line[i] = '\0';}
            }

            switch (switcher)
            {
            case 0: // prints 'line, '
                printf("%s, ", line);
                switcher = 1;
                break;

            case 1: // prints second line next to first line with enter on the end
                printf("%s\n", line);
                switcher = 0;
                break;

            }
        }

        return 0; 
    }
}