#include <iostream>
#include <fstream>
#include <string>
#include "MyStack.h" 

using namespace std;

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '*' || op == '/') return 2;
    else if (op == '^') return 3;
    return 0;
}

string infixToPostfix(const string& infix) {
    string postfix = "";
    MyStackLinkedList operators; 

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (operators.peek() != '(' && operators.peek() != ' ') {
                postfix += operators.pop();
            }
            operators.pop(); 
        }
        else { 
            if (operators.isEmpty() == false) {
                operators.printStack();
            }

            while (getPriority(ch) <= getPriority(operators.peek()) && operators.peek() != ' ') {
                postfix += operators.pop();
            }
            operators.push(ch);
        }  
    }

    while (operators.isEmpty() == false) {
        postfix += operators.pop();
    }

    return postfix;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }
    string infixExpression;
    getline(inputFile, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);
    cout << "postfix: " << postfixExpression << endl;
    return 0;
}
