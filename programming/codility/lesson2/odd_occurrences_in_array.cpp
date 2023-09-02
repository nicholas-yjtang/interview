#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int solution (vector<int>&A) {
    unordered_map<int,int> numbers;
    for (int i = 0; i < (int)A.size(); i++) {
        numbers[A[i]]++;
    }
    for (int i = 0; i < (int)A.size(); i++) {
        if (numbers[A[i]] == 1) return A[i];
    }
    return -1;
}

int main () {
    vector<int> A = {9,3,9,3,9,7,9};
    cout << solution(A) << endl;
}