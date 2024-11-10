# Practical 2
## Aim:
1. **Write a C program to test whether a given identifier is valid or not.**
2. **Write a C program to identify whether a given line is a comment.**
3. **Write a C program to check whether the input string is a keyword, identifier, or constant.**

## Theory: 

#### 1. Testing Validity of Identifiers

**Identifiers** are fundamental components in programming languages, representing variables, functions, types, and more. In the lexical analysis phase of compiler design, the lexer (or lexical analyzer) is responsible for recognizing valid identifiers from the source code.

**Key Rules for Identifiers in C:**
- Must start with a letter (a-z, A-Z) or an underscore (`_`).
- Can only contain letters, digits (0-9), and underscores.
- Must not be a reserved keyword.

#### 2. Identifying Comments

**Comments** in source code are non-executable parts meant for documentation or clarification purposes. They need to be recognized and ignored by the compiler during the lexical analysis phase.

**Types of Comments in C:**
- **Single-line comments:** Start with `//`.
- **Multi-line comments:** Enclosed between `/*` and `*/`.

The lexer must correctly identify and discard comments to avoid processing them as code, which could otherwise lead to syntax errors or misinterpretation of the program structure.

#### 3. Classifying Input Strings: Keywords, Identifiers, or Constants

In compiler design, the lexer’s role includes differentiating between **keywords**, **identifiers**, and **constants**:
- **Keywords** are reserved words that have a special meaning in the language and cannot be used as identifiers (e.g., `int`, `return`, `if`).
- **Identifiers** are user-defined names that represent variables, functions, etc.
- **Constants** are literals or fixed values in the code (e.g., numbers, characters).

## Conclusion:

Through Practical 2, I learned how lexical analysis works in compiler design. By writing programs to validate identifiers, detect comments, and classify strings, I gained practical experience in essential compiler tasks. This exercise helped me understand the importance of accurate tokenization in the compilation process.

## Code:
- First code:
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl",
    "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable",
    "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq",
    "private", "protected", "public", "register", "reinterpret_cast", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
    "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t",
    "while", "xor", "xor_eq"};

string validName(string varName){

    if (!((int(varName[0]) >= 97 && int(varName[0]) <= 122) || (int(varName[0] == 95))))
        return "Variable names must begin with a letter or an underscore (_).";

    for (auto val : varName)
        if ((int(val) >= 32) && (int(val) <= 64))
            return "Variable names cannot contain whitespaces or special characters like !, #, %, etc.";

    for (auto val : keywords)
        if (varName == val)
            return val + " is a reserved keyword in C++.";

    return "Valid Naming";
}

int main(){

    string varName;
    cout << "Enter Variable Name: ";
    getline(cin, varName);

    cout << endl
         << validName(varName) << endl;

    cout << endl;

    return 0;
}
```
- Second code:
```cpp
// To check if the given line is a comment or not.

#include <bits/stdc++.h>
using namespace std;

int main(){
    string a;
    cout << "Enter a  string: ";
    getline(cin, a);

    if ((a[0] == '/' && a[1] == '/') || a.size() == 0){
        cout << "Valid Comment" << endl;
        return 0;
    }
    cout << "Invalid Comment" << endl;
    return 0;
}
```
- Third code:
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl",
    "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable",
    "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq",
    "private", "protected", "public", "register", "reinterpret_cast", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
    "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t",
    "while", "xor", "xor_eq"};

string validKeyword(string varName){

    for (auto val : keywords)
        if (varName == val)
            return val + " is a valid keyword in C++.";

    return "Invalid Keyword";
}

int main(){

    string varName;
    cout << "Enter Keyword: ";
    getline(cin, varName);

    cout << endl
         << validKeyword(varName) << endl;

    cout << endl;

    return 0;
}

```