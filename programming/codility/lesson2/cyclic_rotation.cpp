#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

vector<int> solution(vector<int> &A, int K) {
    vector<int> B(A.size());
    for (int i = 0; i < (int)A.size(); i++) {
        B[(i+K)%A.size()] = A[i]; //simple mod operation on the index, no need to actually "shift"
    }
    return B;
}

int main () {
    vector<int> A = {3,8,9,7,6};
    test(solution(A, 3), {9,7,6,3,8});
    return 0;
}