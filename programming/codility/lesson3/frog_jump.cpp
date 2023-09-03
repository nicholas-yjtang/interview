#include <iostream>
#include "common.h"

using namespace std;

int solution (int X, int Y, int D) {
    int distance = Y-X;
    int jumps = distance/D;
    if (distance%D != 0) jumps++;
    return jumps;
}

int main () {
    test(solution(10,85,30), 3);
    return 0;
}