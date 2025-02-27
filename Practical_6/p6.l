%%
[a] {return 'a';}
[()] {return yytext[0];}
[,] {return ',';}
[ \t\n]+ ; // Ignore whitespace
. {return yytext[0];} // Return any other character
%%
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strlen

// Function declarations
int S();
int L();
int L_prime();

char *input_pointer;
char lookahead;

void next_token() {
    lookahead = *input_pointer++;
}

// Recursive Descent Parsing Functions
int S() {
    if (lookahead == '(') {
        next_token();
        if (L()) {
            if (lookahead == ')') {
                next_token();
                return 1; // Valid
            }
        }
    } else if (lookahead == 'a') {
        next_token();
        return 1; // Valid
    }
    return 0; // Invalid
}

int L() {
    if (S()) {
        if (L_prime()) {
            return 1; // Valid
        }
    }
    return 0; // Invalid
}

int L_prime() {
    if (lookahead == ',') {
        next_token();
        if (S()) {
            return L_prime(); // Recursive call for more elements
        }
        return 0; // Invalid
    }
    // ε (epsilon case, valid by default)
    return 1;
}

int main() {
    char input_string[256];

    printf("Enter a string to validate: ");
    fgets(input_string, sizeof(input_string), stdin);

    // Remove newline character
    size_t len = strlen(input_string);
    if (len > 0 && input_string[len - 1] == '\n') {
        input_string[len - 1] = '\0';
    }

    input_pointer = input_string;
    next_token(); // Initialize lookahead

    if (S() && lookahead == '\0') { // Ensure the entire string is consumed
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}

int yywrap() {
    return 1;
}
