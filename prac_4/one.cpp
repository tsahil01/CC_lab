#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Global variables
map<char, set<char>> first;
map<char, set<char>> follow;
map<char, vector<string>> grammar;
set<char> nullable;

// Helper function to split strings
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

// Compute First sets
void computeFirst(char nonTerminal) {
    if (!first[nonTerminal].empty())
        return;

    for (const string &production : grammar[nonTerminal]) {
        if (production == "ε") {
            first[nonTerminal].insert('ε');
            nullable.insert(nonTerminal);
        } else {
            bool nullableProd = true;
            for (char symbol : production) {
                if (symbol >= 'a' && symbol <= 'z') {
                    first[nonTerminal].insert(symbol);
                    nullableProd = false;
                    break;
                } else {
                    computeFirst(symbol);
                    first[nonTerminal].insert(first[symbol].begin(), first[symbol].end());
                    
                    first[nonTerminal].erase('ε');
                    if (first[symbol].find('ε') == first[symbol].end()) {
                        nullableProd = false;
                        break;
                    }
                }
            }
            if (nullableProd) {
                first[nonTerminal].insert('ε');
            }
        }
    }
}

// Compute Follow sets
void computeFollow(char nonTerminal) {
    if (!follow[nonTerminal].empty())
        return;

    if (nonTerminal == grammar.begin()->first) {
        follow[nonTerminal].insert('$');
    }

    for (const auto &rule : grammar) {
        for (const string &production : rule.second) {
            size_t pos = production.find(nonTerminal);
            while (pos != string::npos) {
                if (pos + 1 < production.length()) {
                    char nextSymbol = production[pos + 1];
                    if (nextSymbol >= 'a' && nextSymbol <= 'z') {
                        follow[nonTerminal].insert(nextSymbol);
                    } else {
                        computeFirst(nextSymbol);
                        follow[nonTerminal].insert(first[nextSymbol].begin(), first[nextSymbol].end());
                        follow[nonTerminal].erase('ε');
                        if (first[nextSymbol].find('ε') != first[nextSymbol].end()) {
                            computeFollow(nextSymbol);
                            follow[nonTerminal].insert(follow[nextSymbol].begin(), follow[nextSymbol].end());
                        }
                    }
                } else {
                    computeFollow(rule.first);
                    follow[nonTerminal].insert(follow[rule.first].begin(), follow[rule.first].end());
                }
                pos = production.find(nonTerminal, pos + 1);
            }
        }
    }
}

int main() {
    // Define grammar
    grammar['S'] = {"AB", "a"};
    grammar['A'] = {"a", "ε"};
    grammar['B'] = {"b"};

    // Compute First sets
    for (const auto &rule : grammar) {
        computeFirst(rule.first);
    }

    // Compute Follow sets
    for (const auto &rule : grammar) {
        computeFollow(rule.first);
    }

    // Display First sets
    cout << "First Sets:\n";
    for (const auto &entry : first) {
        cout << entry.first << ": { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }

    // Display Follow sets
    cout << "\nFollow Sets:\n";
    for (const auto &entry : follow) {
        cout << entry.first << ": { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }

    return 0;
}
