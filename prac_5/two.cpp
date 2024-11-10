#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Grammar rules and parsing table definition
map<pair<char, char>, string> parseTable; // LL(1) parsing table
string terminals = "+*()i"; // Define terminals
string nonTerminals = "ETFXY"; // Define non-terminals

// Function to initialize parsing table (hard-coded example)
void initializeParseTable() {
    parseTable[{'E', 'i'}] = "TX";
    parseTable[{'E', '('}] = "TX";
    parseTable[{'X', '+'}] = "+TX";
    parseTable[{'X', ')'}] = "ε";
    parseTable[{'X', '$'}] = "ε";
    parseTable[{'T', 'i'}] = "FY";
    parseTable[{'T', '('}] = "FY";
    parseTable[{'Y', '*'}] = "*FY";
    parseTable[{'Y', '+'}] = "ε";
    parseTable[{'Y', ')'}] = "ε";
    parseTable[{'Y', '$'}] = "ε";
    parseTable[{'F', 'i'}] = "i";
    parseTable[{'F', '('}] = "(E)";
}

// Function to simulate LL(1) parsing
bool parseString(const string &input) {
    stack<char> parsingStack;
    parsingStack.push('$');  // End marker
    parsingStack.push('E');  // Start symbol

    int i = 0; // Input pointer
    while (!parsingStack.empty()) {
        char top = parsingStack.top();
        char currentInput = input[i];

        // If stack top is a terminal or end marker
        if (top == currentInput) {
            parsingStack.pop();
            i++; // Move to the next input symbol
        } else if (top == '$') {
            return currentInput == '$'; // Successfully parsed if at the end of input
        } else if (isupper(top)) { // If stack top is a non-terminal
            string production = parseTable[{top, currentInput}];
            if (production.empty()) {
                // No rule in parse table, parsing fails
                return false;
            }

            parsingStack.pop();
            if (production != "ε") {
                // Push production in reverse order onto the stack
                for (int j = production.size() - 1; j >= 0; j--) {
                    parsingStack.push(production[j]);
                }
            }
        } else {
            // Stack top is a terminal that doesn't match input, parsing fails
            return false;
        }
    }
    return true;
}

int main() {
    // Initialize the parsing table
    initializeParseTable();

    // Input string to parse (must end with '$' as end marker)
    string input;
    cout << "Enter input string to parse (end with $): ";
    cin >> input;

    // Start parsing
    bool success = parseString(input);
    if (success) {
        cout << "The string was successfully parsed.\n";
    } else {
        cout << "The string was not successfully parsed.\n";
    }

    return 0;
}
