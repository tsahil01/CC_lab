#include <iostream>
#include <string>

using namespace std;

int tempVarCount = 0; // Counter for temporary variables

// Function to generate new temporary variable names (e.g., t1, t2, t3, ...)
string newTemp() {
    tempVarCount++;
    return "t" + to_string(tempVarCount);
}

// Function to generate TAC for an arithmetic expression
void generateTAC(string expr) {
    int len = expr.length();
    string temp1, temp2, tempResult;

    for (int i = 0; i < len; i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // Left operand
            string leftOperand(1, expr[i - 1]);
            // Right operand
            string rightOperand(1, expr[i + 1]);
            // Operator
            char op = expr[i];

            // Generate a new temporary variable to store the result
            tempResult = newTemp();

            // Print the three address code for the current operation
            cout << tempResult << " = " << leftOperand << " " << op << " " << rightOperand << endl;

            // Replace the evaluated part of the expression with the new temporary variable
            expr[i - 1] = tempResult[0];
            expr.erase(i, 2);
            i -= 1; // Adjust position since the expression is shortened
        }
    }
}

int main() {
    string expression;

    // Input an arithmetic expression
    cout << "Enter an arithmetic expression (e.g., a+b*c): ";
    cin >> expression;

    cout << "\nThree Address Code (TAC):\n";

    // Generate and print the TAC for the input expression
    generateTAC(expression);

    return 0;
}
