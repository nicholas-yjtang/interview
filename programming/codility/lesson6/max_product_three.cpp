#include <iostream>
#include <vector>
#include <algorithm>
#include "common.h"

using namespace std;

int solution (vector<int>&A) {
    sort(A.begin(), A.end());
    //maximal product is the last 3 elements
    int max_product = A[A.size()-1] * A[A.size()-2] * A[A.size()-3];
    if (A[0] < 0 && A[1] < 0) {
        //if the first 2 elements are negative, then the product of the first 2 elements and the last element is also a candidate
        int product = A[0] * A[1] * A[A.size()-1];
       if (product > max_product) max_product = product;
    }
    return max_product;
}

int main () {
    vector<int> A = {-3,1,2,-2,5,6};
    test(solution(A), 60);
    A = {-5,5,-5,4};
    test(solution(A), 125);
    return 0;
}