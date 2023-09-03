#include <iostream>
#include <string>
#include <stack>
#include "common.h"
using namespace std;

int solution (string &S) {
    stack<char> brackets;
    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == '(') brackets.push(S[i]);
        else if (S[i] == '[') brackets.push(S[i]);
        else if (S[i] == '{') brackets.push(S[i]);
        else if (S[i] == '}') {
            if (brackets.empty()) return 0;
            if (brackets.top() != '{') return 0;
            brackets.pop();
        }
        else if (S[i] == ']') {
            if (brackets.empty()) return 0;
            if (brackets.top() != '[') return 0;
            brackets.pop();
        }
        else if (S[i] == ')') {
            if (brackets.empty()) return 0;
            if (brackets.top() != '(') return 0;
            brackets.pop();
        }
    }
    if (brackets.empty()) return 1;
    else return 0;
}

int main () {
    string S = "{[()()]}";
    test(solution(S), 1);
    S = "([)()]";
    test(solution(S), 0);
    return 0;
}