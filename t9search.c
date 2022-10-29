#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_RECORD_LEN 100


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

int line_validation(char *line) { // function that tells if line is valid or not - /n should be on the end of line else its too long, if \n is first char then line is blank
    if (line[len(line)] != '\n') {
    fprintf(stderr, "Error: some contacts are too long or there is no new line on the end of file\n");

    return 1;
    }
    if (line[0] == '\n') {
        fprintf(stderr, "Error: blank line has been found\n");

        return 1;
    }

    return 0;
}

int includes(char *big, char small) { // function to check if string contains exact letter returns 1 when it does and 0 when it doesnt
    int len_big = len(big);
    for (int j = 0; j < len_big; j++) {
        if (big[j] == tolower(small)) return 1;
    }
    
    return 0;
}

int is_number(char *str) { // function to check if given sting is number or not
    for (int i = 0; i < len(str); i++) {
        if (includes("0123456789", str[i]) != 1) {
            return 0;
        }
    }

    return 1;
}

int filter(char *text, char *number) {

    int number_len = len(number); // len of given number
    int def = 0; // default - when should it start to search again when there are multiple occurences of same letter
    int iter = 0; // given text iterator
    int match = 0; // match counter
    int auxiliary_filter_found = 0; // variable to store if contact was matched or not

    for (int i = 0; i < number_len; i++) {

        char *letters; // letters

        switch (number[i]) // switch taking number by number - by cycle iterator - and transforming it into letters
        {
            case '1':
                letters = "1";
                break;
            case '2':
                letters = "abc2";
                break;
            case '3':
                letters = "def3";
                break;
            case '4':
                letters = "ghi4";
                break;
            case '5':
                letters = "jkl5";
                break;
            case '6':
                letters = "mno6";
                break;
            case '7':
                letters = "pqrs7";
                break;
            case '8':
                letters = "tuv8";
                break;
            case '9':
                letters = "wxyz9";
                break;
            case '0':
                letters = "+0";
                break;
            default:
                return 0;
        }

        for (int x = 0; x < len(text)-def; x++) { // iterating text
            if (includes(letters, text[iter])!= 0) { // if letter is in transformed number

                iter++; // increment iterator
                match++; // increment match
                if (match == number_len) auxiliary_filter_found += 1; // checking if its OK
                break; // break cycle to continue matching
                }

            def += 1; // if its not wanted letter, increment default to start searching on +1 later position next time (for multiple occurence of same letter)
            iter = def; // iterator is same as def because we are iterating using iterator
            i = -1; // reset main cycle
            match = 0; // reset match counter
            break;
        }
        
    }
    return auxiliary_filter_found;
}

int main(int argc, char *argv[]) {

    if (argc > 2) { // checking if i have correct number of arguments
        fprintf(stderr, "Error: too many arguments, expected 1, taken %d\n", argc-1);
        return 1;
    }

    else if (argc == 2) { // validating number

        if (is_number(argv[1]) != 1) {
        fprintf(stderr, "Error: incorrect number entered, should be number, not text\n");
        return 1;
        }

        char *number = argv[1]; // given number

        char line[MAX_RECORD_LEN]; // declared variable for name-record
        char number_line[MAX_RECORD_LEN]; // declared variable for number-record
        int auxiliary_found = 0; // auxiliary variable to determinate if at least one contact was found or not
        int filter_found; // variable to store if filter found contact or not
        int filter_found_result = 0; // variable to store if filter found at least one contact or not - decides if printf message not found on the end or dont

        while (fgets(line, MAX_RECORD_LEN+2, stdin)) // while records are available
        {
            if(line_validation(line) == 1) {
                return 1;
            }

            char *line_wo_nwl = rem_newline(line); // variable to store name-record without newline
            filter_found = filter(line_wo_nwl, rem_newline(rem_spaces(number))); // filter contact name by given number and save result into variable

            if (filter_found > 0) { // if was successful, increment ff_result and get number line for this contact and print it together
                filter_found_result++;
                fgets(number_line, MAX_RECORD_LEN+2, stdin); // getting number-record and storing into number_line

                if (line_validation(number_line) == 1) {
                    return 1;
                }

                char *number_line_wo_nwl = rem_newline(number_line); // variable to store number-record without newline
                fprintf(stdout, "%s, %s\n", line_wo_nwl, number_line_wo_nwl);

            }

            else if (filter_found == 0) { // if was not successful, get number for this contact and try to find if its wanted number by given number or is not

                fgets(number_line, MAX_RECORD_LEN+2, stdin); // getting number-record and storing into number_line

                if (line_validation(number_line) == 1) {
                    return 1;
                }

                char *number_line_wo_nwl = rem_newline(number_line); // variable to store number-record without newline
                char *edited_number = rem_spaces(number_line); // variable to store number without spaces
                int found = filter(edited_number, number);

            if (found > 0) {auxiliary_found++; fprintf(stdout, "%s, %s\n", line_wo_nwl, number_line_wo_nwl);} // if substring was found increment auxiliary variable and print contact
            }
        }

        if (auxiliary_found == 0 && filter_found_result == 0) {fprintf(stdout, "Not found");} // if none contact was found print message

        return 0;
        
    }


    else { // if no arguments are given, stdout all records

        char line[MAX_RECORD_LEN];
        int switcher = 0; // auxiliary variable to determinate which record belongs to which record

        while (fgets(line, MAX_RECORD_LEN+2, stdin)) {

            if (line_validation(line) == 1) {
                return 1;
            }

            for (int i = 0; i < MAX_RECORD_LEN+2; i++) {    // iterating each line and checkign where does it end, replacing enter with end symbol
                if (line[i] == '\n') {line[i] = '\0';}
            }

            switch (switcher)
            {
            case 0: // prints 'line, '
                fprintf(stdout, "%s, ", line);
                switcher = 1;
                break;

            case 1: // prints second line next to first line with enter on the end
                fprintf(stdout, "%s\n", line);
                switcher = 0;
                break;

            }
        }

        return 0; 
    }
}