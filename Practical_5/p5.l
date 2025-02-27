%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
%}

%option noyywrap

digit [0-9]+
letter [a-zA-Z_][a-zA-Z0-9_]*
ws [ \t\n]+

%%

int { printf("Keyword: %s\n", yytext); }
char { printf("Keyword: %s\n", yytext); }
return { printf("Keyword: %s\n", yytext); }

{letter} { printf("Identifier: %s\n", yytext); }
{digit} { printf("Constant: %s\n", yytext); }
"+"|"-"|"*"|"/"|"%" { printf("Operator: %s\n", yytext); }
"=" { printf("Operator: %s\n", yytext); }
";"|"(" | ")"|"{"|"}" { printf("Punctuation: %s\n", yytext); }

{ws} {/* Ignore white spaces */}

. { printf("Invalid Token: %s\n", yytext); }

%%

int main() {
    FILE *f;
    f = fopen("input.c", "r");
    if (!f) {
        printf("Cannot open file\n");
        return 1;
    }
    yyin = f;
    yylex();
    fclose(f);
    return 0;
}
