#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, vector<string>> grammar; // Stores the grammar rules
map<char, set<char>> firstSets, followSets; // Stores First and Follow sets

// Function to compute First set
void computeFirst(char nonTerminal) {
    if (!firstSets[nonTerminal].empty()) return; // If already computed

    for (const string &production : grammar[nonTerminal]) {
        if (islower(production[0]) || production[0] == '(' || production[0] == ')') {
            firstSets[nonTerminal].insert(production[0]); // Terminal or '('
        } else {
            for (char symbol : production) {
                if (isupper(symbol)) { // Non-terminal
                    computeFirst(symbol);
                    firstSets[nonTerminal].insert(firstSets[symbol].begin(), firstSets[symbol].end());
                    if (firstSets[symbol].find('ε') == firstSets[symbol].end()) break;
                } else {
                    firstSets[nonTerminal].insert(symbol);
                    break;
                }
            }
        }
    }
}

// Function to compute Follow set
void computeFollow(char nonTerminal) {
    if (!followSets[nonTerminal].empty()) return; // If already computed

    if (nonTerminal == 'S') followSets[nonTerminal].insert('$'); // Start symbol

    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        char lhs = it->first;
        for (const string &production : it->second) {
            for (size_t i = 0; i < production.size(); i++) {
                if (production[i] == nonTerminal) {
                    bool epsilonNext = false;
                    for (size_t j = i + 1; j < production.size(); j++) {
                        char nextSymbol = production[j];

                        if (islower(nextSymbol) || nextSymbol == '(' || nextSymbol == ')') {
                            followSets[nonTerminal].insert(nextSymbol);
                            epsilonNext = false;
                            break;
                        } else {
                            followSets[nonTerminal].insert(firstSets[nextSymbol].begin(), firstSets[nextSymbol].end());
                            if (firstSets[nextSymbol].find('ε') == firstSets[nextSymbol].end()) {
                                epsilonNext = false;
                                break;
                            } else {
                                epsilonNext = true;
                            }
                        }
                    }
                    if (epsilonNext || i + 1 == production.size()) {
                        computeFollow(lhs);
                        followSets[nonTerminal].insert(followSets[lhs].begin(), followSets[lhs].end());
                    }
                }
            }
        }
    }
}

// Function to print First and Follow sets
void printSets(const map<char, set<char>> &sets, const string &title) {
    cout << title << ":\n";
    for (auto it = sets.begin(); it != sets.end(); ++it) {
        cout << title << "(" << it->first << ") = { ";
        for (char symbol : it->second) cout << symbol << " ";
        cout << "}\n";
    }
    cout << endl;
}

int main() {
    // Defining the given grammar
    grammar['S'] = {"AB", "D"};
    grammar['A'] = {"a", "ε"};
    grammar['B'] = {"b", "ε"};
    grammar['C'] = {"(S)", "c"};
    grammar['D'] = {"AC"};

    // Compute First sets
    for (auto it = grammar.begin(); it != grammar.end(); ++it) computeFirst(it->first);

    // Compute Follow sets
    for (auto it = grammar.begin(); it != grammar.end(); ++it) computeFollow(it->first);

    // Print results
    printSets(firstSets, "First");
    printSets(followSets, "Follow");

    return 0;
}
