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