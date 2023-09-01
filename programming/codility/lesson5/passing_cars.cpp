#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    //Reverse to find the cumulative west moving cars
    vector<int> west (A.size(), 0);
    for (int i = (int)A.size()-1; i >= 0; i--) {
        if (i == (int)A.size()-1) {
            if (A[i] == 1) west[i] = 1;
            else west[i] = 0;
            continue;
        }
        if (A[i] == 1) west[i] = west[i+1]+1;
        else west[i] = west[i+1];
    }
    //for each east moving car, add the number of west moving cars at that point
    int crossing = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] == 0) {
            crossing+= west[i];
            if (crossing > 1000000000) return -1;
        }
    }
    return crossing;
}



int main() {
    vector<int> A = {0,1,0,1,1};
    cout << solution(A) << endl;
    return 0;
}