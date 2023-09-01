#include <iostream>

using namespace std;

int solution (int X, int Y, int D) {
    int distance = Y-X;
    int jumps = distance/D;
    if (distance%D != 0) jumps++;
    return jumps;
}

int main () {
    cout << solution(10,85,30) << endl;
    return 0;
}