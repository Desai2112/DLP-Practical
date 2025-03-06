#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <regex>
using namespace std;

// Keywords in C
unordered_set<string> keywords = {"int", "char", "return", "void", "long", "struct", "float"};

// Operators and punctuation symbols
unordered_set<char> operators = {'+', '-', '*', '/', '=', '&', '|', '!', '<', '>'};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}', '[', ']'};

// Symbol Table
unordered_set<string> symbolTable;
vector<string> lexicalErrors;

// Token Structure
struct Token {
    string type;
    string value;
};

vector<Token> tokens;

bool isIdentifier(const string &str) {
    return regex_match(str, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

bool isConstant(const string &str) {
    return regex_match(str, regex("[0-9]+(\\.[0-9]+)?"));
}

void processToken(const string &token) {
    if (keywords.count(token)) {
        tokens.push_back({"Keyword", token});
    } else if (isConstant(token)) {
        tokens.push_back({"Constant", token});
    } else if (isIdentifier(token)) {
        tokens.push_back({"Identifier", token});
        symbolTable.insert(token);
    } else {
        lexicalErrors.push_back(token + " invalid lexeme");
    }
}

void lexicalAnalyzer(const string &code) {
    string token;
    bool inString = false;
    char prevChar = '\0';

    for (size_t i = 0; i < code.size(); ++i) {
        char ch = code[i];
        if (ch == '"' || ch == '\'') {
            inString = !inString;
            tokens.push_back({"String", string(1, ch)});
            continue;
        }

        if (inString) {
            token += ch;
            continue;
        }

        if (isspace(ch) || punctuation.count(ch) || operators.count(ch)) {
            if (!token.empty()) {
                processToken(token);
                token.clear();
            }
            if (punctuation.count(ch)) {
                tokens.push_back({"Punctuation", string(1, ch)});
            } else if (operators.count(ch)) {
                tokens.push_back({"Operator", string(1, ch)});
            }
        } else {
            token += ch;
        }
    }

    if (!token.empty()) {
        processToken(token);
    }
}

int main() {
    ifstream file("input.c");
    if (!file) {
        cerr << "Error: Cannot open file!" << endl;
        return 1;
    }

    string code, line;
    while (getline(file, line)) {
        size_t pos;
        if ((pos = line.find("//")) != string::npos) {
            line = line.substr(0, pos);
        }
        code += line + " ";
    }
    file.close();

    lexicalAnalyzer(code);

    cout << "TOKENS\n";
    for (const auto &token : tokens) {
        cout << token.type << ": " << token.value << endl;
    }

    cout << "\nLEXICAL ERRORS\n";
    for (const auto &error : lexicalErrors) {
        cout << error << endl;
    }

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int index = 1;
    for (const auto &symbol : symbolTable) {
        cout << index++ << ") " << symbol << endl;
    }
    return 0;
}