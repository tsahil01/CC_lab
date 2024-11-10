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
