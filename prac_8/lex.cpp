#include <iostream>
#include <string>
#include <vector>

using namespace std;

void lex_analyzer(string expression, string lang) {
    string cppKeyWord[] = {"new", "delete", "this", "true", "false", "null", "bool", "char", "int", "float", "double", "void", "signed", "unsigned", "short", "long", "if", "else", "switch", "case", "default", "while", "do", "for", "break", "continue", "return", "goto", "try", "catch", "throw", "const", "static", "virtual", "class", "struct", "union", "enum", "typedef", "template", "typename", "namespace", "using", "public", "protected", "private", "friend", "operator", "inline", "extern", "volatile", "mutable", "register", "explicit", "export", "asm", "sizeof", "typeid", "dynamic_cast", "static_cast", "const_cast", "reinterpret_cast", "and", "and_eq", "bitand", "bitor", "compl", "not", "not_eq", "or", "or_eq", "xor", "xor_eq"};
    string javaKeyWord[] = {"abstract", "assert", "boolean", "break", "byte", "case", "catch", "char", "class", "const", "continue", "default", "do", "double", "else", "enum", "extends", "final", "finally", "float", "for", "goto", "if", "implements", "import", "instanceof", "int", "interface", "long", "native", "new", "null", "package", "private", "protected", "public", "return", "short", "static", "strictfp", "super", "switch", "synchronized", "this", "throw", "throws", "transient", "try", "void", "volatile", "while"};
    char operators[] = {'*', '+', '-', '/', '=', '<', '>', '&', '|', '!', '%', '^'};
    char punctuations[] = {'(', ')', '{', '}', ',', ';', '[', ']', '.', ':'};
    string result[100];
    int itr = 0, start = 0;

    // Tokenizing the expression
    while (true) {
        int pos = expression.find(' ', start);
        if (pos == string::npos) {
            result[itr++] = expression.substr(start);
            break;
        }
        result[itr++] = expression.substr(start, pos - start);
        start = pos + 1;
    }

    string temp_key[100], temp_operator[100], temp_punctuation[100], temp_identifier[100], constants[100];
    int c = 0, o = 0, p = 0, q = 0, r = 0;

    // Analyzing tokens
    for (int i = 0; i < itr; i++) {
        bool isKeyword = false, isOperator = false, isPunctuation = false;
        string* keyWordList;
        int keywordSize;

        // Choose the keyword list based on the language
        if (lang == "cpp") {
            keyWordList = cppKeyWord;
            keywordSize = sizeof(cppKeyWord) / sizeof(cppKeyWord[0]);
        } else if (lang == "java") {
            keyWordList = javaKeyWord;
            keywordSize = sizeof(javaKeyWord) / sizeof(javaKeyWord[0]);
        }

        // Check if the token is a keyword
        for (int j = 0; j < keywordSize; j++) {
            if (result[i] == keyWordList[j]) {
                temp_key[c++] = result[i];
                isKeyword = true;
                break;
            }
        }

        // Check if the token is an operator
        if (!isKeyword) {
            for (int j = 0; j < sizeof(operators); j++) {
                if (result[i][0] == operators[j]) {
                    temp_operator[o++] = result[i];
                    isOperator = true;
                    break;
                }
            }
        }

        // Check if the token is a punctuation
        if (!isKeyword && !isOperator) {
            for (int j = 0; j < sizeof(punctuations); j++) {
                if (result[i][0] == punctuations[j]) {
                    temp_punctuation[p++] = result[i];
                    isPunctuation = true;
                    break;
                }
            }
        }

        // If the token is neither a keyword, operator, nor punctuation, treat it as an identifier or constant
        if (!isKeyword && !isOperator && !isPunctuation) {
            bool isConstant = true;
            for (char ch : result[i]) {
                if (!isdigit(ch)) {
                    isConstant = false;
                    break;
                }
            }
            if (isConstant) {
                constants[r++] = result[i];
            } else {
                temp_identifier[q++] = result[i];
            }
        }
    }

    // Printing categorized tokens
    cout << "Keywords: ";
    for (int i = 0; i < c; i++) cout << temp_key[i] << " ";
    cout << endl;

    cout << "Operators: ";
    for (int i = 0; i < o; i++) cout << temp_operator[i] << " ";
    cout << endl;

    cout << "Punctuations: ";
    for (int i = 0; i < p; i++) cout << temp_punctuation[i] << " ";
    cout << endl;

    cout << "Identifiers: ";
    for (int i = 0; i < q; i++) cout << temp_identifier[i] << " ";
    cout << endl;

    cout << "Constants: ";
    for (int i = 0; i < r; i++) cout << constants[i] << " ";
    cout << endl;
}

// Driver Code
int main() {
    string input, lang;
    cout << "Choose the language (cpp/java): ";
    cin >> lang;
    cin.ignore(); // To ignore the newline character after the language input
    cout << "Enter the input expression: " << endl;
    getline(cin, input);

    if (lang == "cpp" || lang == "java") {
        lex_analyzer(input, lang);
    } else {
        cout << "Invalid language choice." << endl;
    }
    return 0;
}
