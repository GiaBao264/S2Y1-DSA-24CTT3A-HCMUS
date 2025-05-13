#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// kiểm tra số âm
bool isNegative(const string& s) {
    return !s.empty() && s[0] == '-';
}

// loại bỏ dấu âm
string removeNegative(const string& s) {
    return isNegative(s) ? s.substr(1) : s;
}

// xóa số 0 thừa
string removeZeros(string s) {
    size_t start = s.find_first_not_of('0');
    if (start != string::npos) {
        s = s.substr(start);
    }
    else {
        s = "0";
    }
    return s;
}

// so sánh 2 số không dấu
int compareNumbers(const string& a, const string& b) {
    string magA = removeZeros(a);
    string magB = removeZeros(b);
    if (magA.size() > magB.size()) return 1;
    if (magA.size() < magB.size()) return -1;
    for (size_t i = 0; i < magA.size(); ++i) {
        if (magA[i] > magB[i]) return 1;
        if (magA[i] < magB[i]) return -1;
    }
    return 0;
}

// công 2 số lớn
string sumNumbers(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? a[i--] - '0' : 0;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;
        int sum = digitA + digitB + carry;
        carry = sum / 10;
        result = to_string(sum % 10) + result;
    }
    return result;
}

// trừ hai số lớn (a >= b)  
string subtractNumbers(const string& a, const string& b) {
    string result;
    int borrow = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0) {
        int digitA = a[i--] - '0' - borrow;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;
        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result = to_string(digitA - digitB) + result;
    }
    return removeZeros(result);
}

// nhân số lớn với một số
string multiplyByDigit(const string& a, int d) {
    if (d == 0) return "0";
    string result;
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        int digit = a[i] - '0';
        int product = digit * d + carry;
        carry = product / 10;
        result = to_string(product % 10) + result;
    }
    if (carry > 0) result = to_string(carry) + result;
    return result;
}

// nhân hai số không dấu
string multiplyNumbers(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    string result = "0";
    int distance = 0;
    for (int i = b.size() - 1; i >= 0; --i) {
        int digit = b[i] - '0';
        string temp = multiplyByDigit(a, digit);
        for (int k = 0; k < distance; ++k) temp += "0";
        result = sumNumbers(result, temp);
        ++distance;
    }
    return result;
}

// chia hai số không dấu (nguyên)
string divideNumbers(const string& a, const string& b) {
    if (b == "0") throw "Division by zero.";
    if (compareNumbers(a, b) < 0) return "0";
    string quotient;
    string prefix;
    size_t index = 0;
    while (index < a.size() && compareNumbers(prefix, b) < 0) {
        prefix += a[index++];
    }
    while (index <= a.size()) {
        if (compareNumbers(prefix, b) >= 0) {
            int d = 0;
            for (int i = 1; i <= 9; ++i) {
                string temp = multiplyByDigit(b, i);
                if (compareNumbers(temp, prefix) > 0) break;
                d = i;
            }
            string product = multiplyByDigit(b, d);
            prefix = subtractNumbers(prefix, product);
            quotient += to_string(d);
        }
        else {
            quotient += "0";
        }
        if (index < a.size()) prefix += a[index++];
        else break;
        prefix = removeZeros(prefix);
    }
    return removeZeros(quotient);
}

// cộng hai số có dấu
string sumNegative(const string& a, const string& b) {
    bool negA = isNegative(a);
    bool negB = isNegative(b);
    string magA = removeNegative(a);
    string magB = removeNegative(b);
    if (!negA && !negB) return sumNumbers(magA, magB);
    if (negA && negB) return "-" + sumNumbers(magA, magB);
    if (!negA && negB) {
        int cmp = compareNumbers(magA, magB);
        if (cmp > 0) return subtractNumbers(magA, magB);
        if (cmp < 0) return "-" + subtractNumbers(magB, magA);
        return "0";
    }
    int cmp = compareNumbers(magA, magB);
    if (cmp < 0) return subtractNumbers(magB, magA);
    if (cmp > 0) return "-" + subtractNumbers(magA, magB);
    return "0";
}

// trừ hai số có dấu
string subtractNegative(const string& a, const string& b) {
    string negB = isNegative(b) ? removeNegative(b) : "-" + b;
    return sumNegative(a, negB);
}

// nhân hai số có dấu
string multiplyNegative(const string& a, const string& b) {
    bool negA = isNegative(a);
    bool negB = isNegative(b);
    string magA = removeNegative(a);
    string magB = removeNegative(b);
    string result = multiplyNumbers(magA, magB);
    return (negA == negB) ? result : "-" + result;
}

// chia hai số có dấu
string divideNegative(const string& a, const string& b) {
    if (b == "0") throw "Division by zero.";
    bool negA = isNegative(a);
    bool negB = isNegative(b);
    string magA = removeNegative(a);
    string magB = removeNegative(b);
    string result = divideNumbers(magA, magB);
    return (negA == negB) ? result : "-" + result;
}

// kiểm tra có phải là số không
bool isNumber(const string& s) {
    if (s.empty()) return false;
    size_t start = isNegative(s) ? 1 : 0;
    if (start == s.size()) return false;
    for (size_t i = start; i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

// phân tích biểu thức thành tokens
vector<string> getTokens(const string& expr) {
    vector<string> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        if (isspace(expr[i])) {
            ++i;
            continue;
        }
        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+' || expr[i] == '*' || expr[i] == '/') {
            tokens.push_back(string(1, expr[i]));
            ++i;
        }
        else if (expr[i] == '-') {
            if (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/') {
                size_t start = i++;
                while (i < expr.size() && isdigit(expr[i])) ++i;
                tokens.push_back(expr.substr(start, i - start));
            }
            else {
                tokens.push_back("-");
                ++i;
            }
        }
        else if (isdigit(expr[i])) {
            size_t start = i;
            while (i < expr.size() && isdigit(expr[i])) ++i;
            tokens.push_back(expr.substr(start, i - start));
        }
        else {
            throw "Invalid character.";
        }
    }
    return tokens;
}

// mức độ ưu tiên của toán tử
int operatorPriority(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// chuyển từ infix sang postfix
vector<string> convertToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> operators;
    for (size_t i = 0; i < tokens.size(); ++i) {
		const string& token = tokens[i];
        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
            else throw "Missing opening parenthesis.";
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (i + 1 >= tokens.size() || (!isNumber(tokens[i + 1]) && tokens[i + 1] != "(")) {
                throw "Error";
            }
            while (!operators.empty() && operators.top() != "(" && operatorPriority(operators.top()) >= operatorPriority(token)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
		}
    }
    while (!operators.empty()) {
        if (operators.top() == "(") throw "Missing opening parenthesis.";
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

// tính toán biểu thức postfix
string calculatePostfix(const vector<string>& postfix) {
    stack<string> stack;
    for (const string& token : postfix) {
        if (isNumber(token)) {
            stack.push(token);
        }
        else {
            string b = stack.top(); stack.pop();
            string a = stack.top(); stack.pop();
            string result;
            if (token == "+") result = sumNegative(a, b);
            else if (token == "-") result = subtractNegative(a, b);
            else if (token == "*") result = multiplyNegative(a, b);
            else if (token == "/") result = divideNegative(a, b);
            stack.push(result);
        }
    }
    if (stack.size() != 1) throw "Invalid expression.";
    return stack.top();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file." << endl;
        return 1;
    }
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (!in.is_open() || !out.is_open()) {
        cerr << "Cant open file." << endl;
        return 1;
    }
    string line;
    while (getline(in, line)) {
        try {
            vector<string> tokens = getTokens(line);
            vector<string> postfix = convertToPostfix(tokens);
            string result = calculatePostfix(postfix);
            out << result << endl;
            cout << result << endl;
        }
        catch (const char* e) {
            out << "Error" << endl;
            cout << "Error" << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}