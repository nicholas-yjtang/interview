#include <vector>
#include <iostream>
#include <string>
#include "common.h"

using namespace std;

int solution(vector<int> &A) {
    if (A.empty()) return 0;
    //need to take care of possible negative numbers
    int max_ending = A[0] < 0 ? A[0] : 0;
    int max_slice = A[0] < 0 ? A[0] : 0;
    //max slice seen is the maximum sum of a slice ending at index i
    //which either includes A[i] and all A[j] such that j < i
    //or just A[i]
    for (int i = 0; i < (int)A.size(); i++) {
        max_ending = max(A[i], max_ending + A[i]); 
        max_slice = max(max_slice, max_ending);

    }
    return max_slice;
}

int naive_solution(vector<int> &A) {
    if (A.empty()) return 0;
    int max_slice = A[0] < 0 ? A[0] : 0;
    for (int i = 0; i< (int)A.size(); i++) {
        int slice = 0;
        for (int j = i; j < (int)A.size(); j++) {
            slice += A[j];
            max_slice = max(max_slice, slice);
        }
    }
    return max_slice;
}

int main () {
    vector<int> A = {3,2,-6,4,0};
    test(solution(A),5);
    test(A, solution, naive_solution);
    A = {-10};
    test(solution(A),-10);
    test(A, solution, naive_solution);
    return 0;
}
