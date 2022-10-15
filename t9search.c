#include <stdio.h>
#include <string.h>
#define MAX_RECORD_LEN 100
//TODO tolowercase names
/*int count_lines() { // function to count and return how many records do i have from stdin
    char line[MAX_RECORD_LEN];
    int counter = 0;

    while (fgets(line, MAX_RECORD_LEN+1, stdin))
    {
        counter += 1;
    }

    return counter;
    
}*/

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

int len(char *str) { // function that returns len of given string
    int counter = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] != '\n' && str[i] != '\0') {
        counter += 1;
        }
        i++;
    }
    

    return counter;
}

int includes(char *big, char small) { // function to check if string contains exact letter returns 1 when it does and 0 when it doesnt
    int len_big = len(big);
    for (int j = 0; j < len_big; j++) {
        if (big[j] == small) return 1;
    }
    
    return 0;
}

int filter(char *number) {

    int number_len = len(number); // len of given number
    char *text = "petr novak"; // text - remake to universal - to take line
    int def = 0; // default - when should it start to search again when there are multiple occurences of same letter
    int iter = 0; // given text iterator
    int match = 0; // match counter

    for (int i = 0; i < number_len; i++) {

        char *letters; // letters
        switch (number[i]) // switch taking number by number - by cycle iterator - and transforming it into letters
        {
            case '2':
                letters = "abc";
                break;
            case '3':
                letters = "def";
                break;
            case '4':
                letters = "ghi";
                break;
            case '5':
                letters = "jkl";
                break;
            case '6':
                letters = "mno";
                break;
            case '7':
                letters = "pqrs";
                break;
            case '8':
                letters = "tuv";
                break;
            case '9':
                letters = "wxyz";
                break;
        }

        for (int x = 0; x < len(text); x++) { // iterating text
            if (includes(letters, text[iter])!= 0) { // if letter is in transformed number
                printf("text iter true: %c, letters: %s, iter: %d, i: %d\n", text[iter], letters, iter, i);
                iter++; // increment iterator
                match++; // increment match
                if (match == number_len) {printf("SHODA\n");} // checking if its OK
                break; // break cycle to continue matching
                }

            def += 1; // if its not wanted letter, increment default to start searching on +1 later position next time (for multiple occurence of same letter)
            iter = def; // iterator is same as def because we are iterating through iterator
            i = 0; // reset main cycle
            match = 0; // reset match counter
        }
        
    }
    return 0;
}

int main(int argc, char *argv[]) {
    filter("668");
    if (argc > 2) { // checking if i have correct number of arguments
        printf("Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }


    else if (argc == 2) {
        
        char *number = argv[1]; // given number

        char line[MAX_RECORD_LEN]; // declared variable for name-record
        char number_line[MAX_RECORD_LEN]; // declared variable for number-record
        int auxiliary_found = 0; // auxiliary variable to determinate if at least one contact was found or not

        while (fgets(line, MAX_RECORD_LEN+1, stdin)) // while records are available
        {
            char *line_wo_nwl = rem_newline(line); // variable to store name-record without newline
            char *number_line_wo_nwl = rem_newline(number_line); // variable to store number-record without newline

            fgets(number_line, MAX_RECORD_LEN+1, stdin); // getting number-record and storing into number_line

            char *edited_number = rem_spaces(number_line); // variable to store number without spaces
            char *found = strstr(edited_number, number); // variable to store if substring was found or not

            if (found != NULL) {auxiliary_found++; printf("NALEZENO: %s, %s\n", line_wo_nwl, number_line_wo_nwl);} // if substring was found increment auxiliary variable and print contact
        }

        if (auxiliary_found == 0) {printf("Not found");} // if none contact was found print message

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