#include <iostream>
#include "common.h"
using namespace std;

int solution (int A, int B, int K) {
    int count = 0;
    int start = A % K == 0 ? A : A + (K - A % K); //move the start to the first divisible number
    int end = B % K == 0 ? B : B - B % K; //move the end to the last divisible number
    if (start > end) return 0;
    count = (end - start) / K + 1;
    return count;
}

int main () {
    test(solution(6,11,2), 3);
    return 0;
}