#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

// Define grammar rules and symbols
map<char, vector<string>> grammar; // grammar rules
map<char, set<char>> firstSet;     // FIRST sets
map<char, set<char>> followSet;    // FOLLOW sets
map<pair<char, char>, string> parseTable; // LL(1) parsing table

// Function to add grammar rules
void addRule(char nonTerminal, const string &rule) {
    grammar[nonTerminal].push_back(rule);
}

// Function to calculate FIRST set for a symbol
set<char> computeFirst(char symbol) {
    if (firstSet.count(symbol)) return firstSet[symbol];
    set<char> first;
    if (!isupper(symbol)) {
        first.insert(symbol);
    } else {
        for (auto &rule : grammar[symbol]) {
            for (auto &ch : rule) {
                set<char> temp = computeFirst(ch);
                first.insert(temp.begin(), temp.end());
                if (temp.find('ε') == temp.end()) break;
            }
        }
    }
    firstSet[symbol] = first;
    return first;
}

// Function to calculate FOLLOW set for a non-terminal
void computeFollow(char nonTerminal) {
    if (followSet.count(nonTerminal)) return;
    for (auto &[lhs, rules] : grammar) {
        for (auto &rule : rules) {
            for (size_t i = 0; i < rule.size(); i++) {
                if (rule[i] == nonTerminal) {
                    if (i + 1 < rule.size()) {
                        set<char> firstOfNext = computeFirst(rule[i + 1]);
                        followSet[nonTerminal].insert(firstOfNext.begin(), firstOfNext.end());
                        followSet[nonTerminal].erase('ε');
                    }
                    if (i + 1 == rule.size() || firstSet[rule[i + 1]].count('ε')) {
                        computeFollow(lhs);
                        followSet[nonTerminal].insert(followSet[lhs].begin(), followSet[lhs].end());
                    }
                }
            }
        }
    }
}

// Function to generate the predictive parsing table
void generateParseTable() {
    for (auto &[nonTerminal, rules] : grammar) {
        for (auto &rule : rules) {
            set<char> first = computeFirst(rule[0]);
            for (char symbol : first) {
                if (symbol != 'ε') {
                    parseTable[{nonTerminal, symbol}] = rule;
                }
            }
            if (first.count('ε')) {
                for (char symbol : followSet[nonTerminal]) {
                    parseTable[{nonTerminal, symbol}] = rule;
                }
            }
        }
    }
}

// Function to display the parse table
void displayParseTable() {
    cout << "Predictive Parsing Table:\n";
    for (auto &[key, rule] : parseTable) {
        cout << "M[" << key.first << ", " << key.second << "] = " << rule << "\n";
    }
}

int main() {
    // Add grammar rules here
    addRule('E', "TX");
    addRule('X', "+TX");
    addRule('X', "ε");
    addRule('T', "FY");
    addRule('Y', "*FY");
    addRule('Y', "ε");
    addRule('F', "(E)");
    addRule('F', "i");

    // Compute FIRST and FOLLOW sets
    for (auto &[nonTerminal, _] : grammar) {
        computeFirst(nonTerminal);
        computeFollow(nonTerminal);
    }

    // Generate parsing table
    generateParseTable();
    displayParseTable();

    return 0;
}
