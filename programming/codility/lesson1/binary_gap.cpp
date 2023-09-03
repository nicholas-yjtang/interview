#include <iostream>
#include "common.h"

using namespace std;

int solution(int N) {
    int max_gap = 0;
    int current_gap = 0;
    bool started = false;
    while (N>0) {
        if (N%2==1) {
            //start the gap counting
            if (!started) {
                started = true;
            }
            //restart the gap counting
            else {
                if (current_gap > max_gap) max_gap = current_gap;
                current_gap = 0;
            }            
        }
        else if (started) {
            current_gap++;            
        }
        //shift the bits
        N >>= 1;
    }
    return max_gap;
}

int main () {

    test(solution(9), 2);
    test(solution(529), 4);
    test(solution(20), 1);
    test(solution(15), 0);
    test(solution(32), 0);
    test(solution(1041), 5);
    test(solution(74901729), 4);
    return 0;
}