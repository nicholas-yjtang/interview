#include <iostream>
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
    cout << solution(1041) << endl; //5
    cout << solution(32) << endl; //0
    cout << solution(15) << endl; //0
    cout << solution(74901729) << endl; //4
    return 0;
}