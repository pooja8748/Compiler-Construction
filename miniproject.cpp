#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to tokenize the input string
vector<string> tokenize(const string& code) {
    vector<string> tokens;
    stringstream ss(code);
    string token;
    while (ss >> token) {
        // Handle parentheses and semicolons as separate tokens
        string temp;
        for (char c : token) {
            if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
                if (!temp.empty()) {
                    tokens.push_back(temp);
                    temp.clear();
                }
                tokens.push_back(string(1, c));
            } else {
                temp += c;
            }
        }
        if (!temp.empty()) {
            tokens.push_back(temp);
        }
    }
    return tokens;
}

// Function to check if parentheses/braces are balanced
bool isBalanced(const vector<string>& tokens) {
    stack<char> s;
    for (const string& token : tokens) {
        if (token == "(" || token == "{") {
            s.push(token[0]);
        } else if (token == ")") {
            if (s.empty() || s.top() != '(') return false;
            s.pop();
        } else if (token == "}") {
            if (s.empty() || s.top() != '{') return false;
            s.pop();
        }
    }
    return s.empty();
}

// Function to validate loop syntax
string validateLoop(const vector<string>& tokens) {
    bool isForLoop = false;
    bool isWhileLoop = false;

    // Check if it's a 'for' or 'while' loop
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "for") {
            isForLoop = true;
            break;
        } else if (tokens[i] == "while") {
            isWhileLoop = true;
            break;
        }
    }

    if (!isForLoop && !isWhileLoop) {
        return "Error: No loop found.";
    }

    // Check balanced parentheses/braces
    if (!isBalanced(tokens)) {
        return "Error: Unbalanced parentheses/braces.";
    }

    // Additional checks for 'for' loop
    if (isForLoop) {
        int semicolonCount = count(tokens.begin(), tokens.end(), ";");
        if (semicolonCount != 2) {
            return "Error: 'for' loop must have exactly 2 semicolons.";
        }
    }

    return "Valid Loop Syntax!";
}

int main() {
    string input;
    cout << "Enter a loop (for/while): ";
    getline(cin, input);

    vector<string> tokens = tokenize(input);
    string result = validateLoop(tokens);

    cout << "Result: " << result << endl;

    return 0;
}