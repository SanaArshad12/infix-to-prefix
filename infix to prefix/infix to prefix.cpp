#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPrefix(const string& infix) {
    stack<char> operators;
    string prefix;

    // Reverse the infix expression
    string reversedInfix = infix;
    reverse(reversedInfix.begin(), reversedInfix.end());

    for (char c : reversedInfix) {
        // If character is operand, add to the prefix string
        if (isalnum(c))
            prefix += c;
        // If character is closing parenthesis, push to the stack
        else if (c == ')')
            operators.push(c);
        // If character is opening parenthesis, pop until matching closing parenthesis
        else if (c == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            // Pop the closing parenthesis
            operators.pop();
        }
        // If character is an operator
        else if (isOperator(c)) {
            // Pop operators with higher or equal precedence and add to prefix
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                prefix += operators.top();
                operators.pop();
            }
            // Push current operator to stack
            operators.push(c);
        }
    }

    // Pop remaining operators and add to prefix
    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    // Reverse the prefix string to get the final result
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main() {
    string infixExpression;
    cout << "Enter infix expression: ";
    cin >> infixExpression;

    string prefixExpression = infixToPrefix(infixExpression);
    cout << endl;
    cout << "Prefix expression: " << prefixExpression << endl;

    return 0;
}
