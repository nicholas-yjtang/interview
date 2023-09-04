#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include "common.h"
using namespace std;

int solution(vector<int> &A) {
    stack<int> dominators;
    //to determine the dominator, simply pair up the elements in the array, if they are the same, push them to the stack, 
    //if they are different, pop them out
    for (int i = 0; i < (int)A.size(); i++) {
        if (dominators.empty()) dominators.push(A[i]);
        else {
            if (dominators.top() != A[i]) dominators.pop();
            else dominators.push(A[i]);
        }
    }
    if (dominators.empty()) return -1;
    int candidate = dominators.top();
    int count = 0;
    int index = -1;
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] == candidate) {
            count++;
            index = i; //always returns the last index of the candidate
        }
    }
    if ((float)count/A.size() > 0.5) return index;
    else return -1;    

}

int naive_solution(vector<int> &A) {
    unordered_map<int,int> numbers;
    //just add all numbers to the map, the number of unique numbers is the size of the map
    for (int i = 0; i < (int)A.size(); i++) {
        numbers[A[i]]++;
    }
    for (auto number: numbers) {
        if (number.second > (int)A.size()/2) {
            for (int i = (int)A.size()-1; i >= 0; i--) {
                if (A[i] == number.first) return i;
            }
        }
    }
    return -1;
}

int main () {
    vector<int> A = {3,4,3,2,3,-1,3,3};
    test(A, solution, naive_solution);
    return 0;
}