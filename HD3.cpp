#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BasicCalculator {
public:
    int calculate(string s) {
        stack<int> values;     // Stack to hold values
        stack<int> operators;  // Stack to hold signs (1 for +, -1 for -)
        int result = 0, num = 0, sign = 1;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];

            if (isdigit(c)) {
                // Form the number
                num = num * 10 + (c - '0');
            } else if (c == '+' || c == '-') {
                // Add the previous number to the result
                result += sign * num;
                num = 0;

                // Update the sign for the next number
                sign = (c == '+') ? 1 : -1;
            } else if (c == '(') {
                // Push the result and sign onto their stacks
                values.push(result);
                operators.push(sign);

                // Reset result and sign for the new sub-expression
                result = 0;
                sign = 1;
            } else if (c == ')') {
                // Add the current number to the result
                result += sign * num;
                num = 0;

                // Multiply by the sign from the stack and add to the previous result
                result = values.top() + operators.top() * result;
                values.pop();
                operators.pop();
            }
        }

        // Add any remaining number to the result
        result += sign * num;
        return result;
    }
};

int main() {
    BasicCalculator calculator;

    // Test cases
    string s1 = "1 + 1";
    string s2 = " 2-1 + 2 ";
    string s3 = "(1+(4+5+2)-3)+(6+8)";

    cout << "Input: \"" << s1 << "\" -> Output: " << calculator.calculate(s1) << endl;
    cout << "Input: \"" << s2 << "\" -> Output: " << calculator.calculate(s2) << endl;
    cout << "Input: \"" << s3 << "\" -> Output: " << calculator.calculate(s3) << endl;

    return 0;
}
