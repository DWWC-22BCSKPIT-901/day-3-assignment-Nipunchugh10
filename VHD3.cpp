#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
using namespace std;

class LispParser {
public:
    int evaluate(string expression) {
        unordered_map<string, vector<int>> scope;
        return evaluate(expression, scope);
    }

private:
    // Helper function to evaluate the expression with a given scope
    int evaluate(const string& expr, unordered_map<string, vector<int>>& scope) {
        if (isdigit(expr[0]) || expr[0] == '-') { // Direct integer
            return stoi(expr);
        }
        if (isalpha(expr[0]) && scope.count(expr)) { // Variable lookup
            return scope[expr].back();
        }

        stringstream ss(expr.substr(1, expr.size() - 2)); // Remove outer parentheses
        string command;
        ss >> command;

        if (command == "let") {
            return evaluateLet(ss, scope);
        } else if (command == "add") {
            return evaluateAdd(ss, scope);
        } else if (command == "mult") {
            return evaluateMult(ss, scope);
        }
        return 0;
    }

    int evaluateLet(stringstream& ss, unordered_map<string, vector<int>>& scope) {
        string token;
        vector<string> variables;

        while (ss >> token) {
            if (isExpression(token)) { // The final expression
                int result = evaluate(token, scope);
                for (const string& var : variables) {
                    scope[var].pop_back(); // Remove variables from this scope
                    if (scope[var].empty()) {
                        scope.erase(var);
                    }
                }
                return result;
            }

            string valueExpr;
            ss >> valueExpr;
            int value = evaluate(valueExpr, scope);

            scope[token].push_back(value); // Add variable to current scope
            variables.push_back(token);
        }
        return 0; // Should never reach here
    }

    int evaluateAdd(stringstream& ss, unordered_map<string, vector<int>>& scope) {
        string expr1, expr2;
        ss >> expr1 >> expr2;
        return evaluate(expr1, scope) + evaluate(expr2, scope);
    }

    int evaluateMult(stringstream& ss, unordered_map<string, vector<int>>& scope) {
        string expr1, expr2;
        ss >> expr1 >> expr2;
        return evaluate(expr1, scope) * evaluate(expr2, scope);
    }

    bool isExpression(const string& token) {
        return token[0] == '(' || isdigit(token[0]) || token[0] == '-' || isalpha(token[0]);
    }
};

int main() {
    LispParser parser;

    // Test cases
    string expr1 = "(let x 2 (mult x (let x 3 y 4 (add x y))))";
    string expr2 = "(let x 3 x 2 x)";
    string expr3 = "(let x 1 y 2 x (add x y) (add x y))";

    cout << "Input: \"" << expr1 << "\" -> Output: " << parser.evaluate(expr1) << endl;
    cout << "Input: \"" << expr2 << "\" -> Output: " << parser.evaluate(expr2) << endl;
    cout << "Input: \"" << expr3 << "\" -> Output: " << parser.evaluate(expr3) << endl;

    return 0;
}
