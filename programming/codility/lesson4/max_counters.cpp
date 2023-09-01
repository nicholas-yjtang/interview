#include <vector>
#include <iostream>
#include "common.h"

using namespace std;

vector<int> solution (int N, vector<int> & A) {
    vector<int> counters(N,0);
    int max = 0;
    int floor = 0; //instead of adding 1 to all counters, we keep track of the floor
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] == N+1) { //max counter operation
            floor = max;
            continue;
        }
        //before we increment, check that we meet the floor minimally
        if (counters[A[i]-1] < floor) counters[A[i]-1] = floor;
        counters[A[i]-1]++;
        //set the max to the current counter if it is greater than the max
        if (counters[A[i]-1] > max) max = counters[A[i]-1];        
    }

    //check that all counters meet the floor
    for (int i = 0; i < N; i++) {
        if (counters[i] < floor) counters[i] = floor;
    }
    return counters;
}

int main () {
    int N = 5;
    vector<int> A = {3,4,4,N+1,1,4,4};
    vector<int> B = solution(5,A);
    print_vector(B);
    N=1;
    A = {2,1,1,2,1};
    B = solution(N,A);
    print_vector(B);
}