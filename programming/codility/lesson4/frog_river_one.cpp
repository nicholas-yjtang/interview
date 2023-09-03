#include <iostream>
#include <vector>
#include <unordered_map>
#include "common.h"

using namespace std;

int solution(int X, vector<int> &A) {
    unordered_map<int,int> leaves;
    for (int i = 0; i < (int)A.size(); i++) {
        if (leaves[A[i]] == 0) {
            leaves[A[i]]++;
        }
        // assume that the leaves are numbered from 1 to X
        // so once the size of the map is equal to X, we have all the leaves
        if ((int)leaves.size() == X) {
            return i;
        }
    }
    return -1;
}

int main () {
    vector<int> A = {1,3,1,4,2,3,5,4};
    test(solution(5, A), 6);    
    return 0;
}