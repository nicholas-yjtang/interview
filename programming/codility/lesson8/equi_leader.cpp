#include <iostream>
#include <vector>
#include <stack>
#include "common.h"

using namespace std;

int solution (vector<int> & A) {
    vector<int> leaders;
    stack<int> stack;
    for (int i = 0; i < (int)A.size(); i++) {
        if (stack.empty()) stack.push(A[i]);
        else if (stack.top() == A[i]) stack.push(A[i]);
        else stack.pop();
    }
    if (stack.empty()) return 0;
    int candidate = stack.top();
    int total_leader_count = 0; //total number of occurences of the candidate
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] == candidate) total_leader_count++;
    }
    if (total_leader_count <= (int)A.size()/2) return 0;
    int current_leader_count = 0;
    int equi_leaders = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] == candidate) current_leader_count++; //current number of occurences of the candidate
        //calculate the number of leaders in the left and right parts of the array
        //if both are leaders, then we have an equi leader
        if (current_leader_count /(float)(i+1)> 0.5 && (total_leader_count - current_leader_count)/(float) ((int)A.size() - i - 1)> 0.5) equi_leaders++;
    }
    return equi_leaders;
}

int main () {
    vector<int> A = {4,3,4,4,4,2};
    test(solution(A), 2);
    return 0;
}