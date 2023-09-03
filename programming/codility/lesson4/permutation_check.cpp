#include <iostream>
#include <vector>
#include <unordered_map>
#include "common.h"

using namespace std;

int solution(vector<int> &A) {
    unordered_map<int,int> numbers;
    //add all numbers to the map
    for (int i = 0; i < (int)A.size(); i++) {
        numbers[A[i]]++;
    }
    //check if all numbers from 1 to the size of the array are in the map
    for (int i = 1; i <= (int)A.size(); i++) {
        if (numbers[i] == 0) return 0;
    }
    return 1;
}

int main () {
    vector <int> A = {4,1,3,2};
    test(solution(A), 1);
}