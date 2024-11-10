#include <bits/stdc++.h>

using namespace std;

// Token types
enum class TokenType {
    KEYWORD, IDENTIFIER, CONSTANT, OPERATOR, PUNCTUATION, UNKNOWN
};

// Token structure
struct Token {
    TokenType type;
    string value;
};

// Keywords and operators
const unordered_set<string> keywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "class", "compl", "const",
        "const_cast", "continue", "decltype", "default", "delete", "do", "double",
        "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false",
        "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable",
        "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
        "struct", "switch", "template", "this", "thread_local", "throw", "true",
        "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
    };
const unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>'};
const unordered_set<char> punctuations = {';', ',', '(', ')', '{', '}'};

// Function to identify the type of a token
TokenType getTokenType(const string& token) {
    if (keywords.find(token) != keywords.end()) {
        return TokenType::KEYWORD;
    }
    if (isdigit(token[0])) {
        return TokenType::CONSTANT;
    }
    return TokenType::IDENTIFIER;
}

// Function to tokenize the input
vector<Token> lex(const string& code) {
    vector<Token> tokens;
    string currentToken;
   
    for (char ch : code) {
        if (isspace(ch)) {
            if (!currentToken.empty()) {
                TokenType type = getTokenType(currentToken);
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
        } else if (isalnum(ch) || ch == '_') {
            currentToken += ch;
        } else {
            if (!currentToken.empty()) {
                TokenType type = getTokenType(currentToken);
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
           
            if (operators.find(ch) != operators.end()) {
                tokens.push_back({TokenType::OPERATOR, string(1, ch)});
            } else if (punctuations.find(ch) != punctuations.end()) {
                tokens.push_back({TokenType::PUNCTUATION, string(1, ch)});
            } else {
                tokens.push_back({TokenType::UNKNOWN, string(1, ch)});
            }
        }
    }
   
    if (!currentToken.empty()) {
        TokenType type = getTokenType(currentToken);
        tokens.push_back({type, currentToken});
    }
   
    return tokens;
}

// Function to print tokens and counts
void printTokens(const vector<Token>& tokens) {
    int keywordCount = 0;
    int identifierCount = 0;
    int constantCount = 0;
    int operatorCount = 0;
    int punctuationCount = 0;
    int unknownCount = 0;
   
    for (const auto& token : tokens) {
        string typeName;
        switch (token.type) {
            case TokenType::KEYWORD:
                typeName = "KEYWORD";
                keywordCount++;
                break;
            case TokenType::IDENTIFIER:
                typeName = "IDENTIFIER";
                identifierCount++;
                break;
            case TokenType::CONSTANT:
                typeName = "CONSTANT";
                constantCount++;
                break;
            case TokenType::OPERATOR:
                typeName = "OPERATOR";
                operatorCount++;
                break;
            case TokenType::PUNCTUATION:
                typeName = "PUNCTUATION";
                punctuationCount++;
                break;
            default:
                typeName = "UNKNOWN";
                unknownCount++;
                break;
        }
        cout << "Type: " << typeName << ", Value: " << token.value << endl;
    }
   
    // Print counts of each type
    cout << "\nCounts:\n";
    cout << "KEYWORDS: " << keywordCount << endl;
    cout << "IDENTIFIERS: " << identifierCount << endl;
    cout << "CONSTANTS: " << constantCount << endl;
    cout << "OPERATORS: " << operatorCount << endl;
    cout << "PUNCTUATIONS: " << punctuationCount << endl;
    cout << "UNKNOWN: " << unknownCount << endl;
    cout << "Total Count: " << (keywordCount + identifierCount + constantCount + operatorCount + punctuationCount + unknownCount) << endl;
}

int main() {
    string code;
    cout << "Enter code: ";
    getline(cin, code);

    vector<Token> tokens = lex(code);
    printTokens(tokens);

    return 0;
}