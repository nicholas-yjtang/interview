#include <iostream>
#include <vector>
#include <stack>
#include "common.h"

using namespace std;

int solution (vector<int>&A, vector<int> &B) {

    stack<int> fish_downstream;
    int fish_alive = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        if (B[i] == 1) { //fish going downstream
            fish_downstream.push(A[i]);
        } 
        else { 
            //a fish going upstream, and since i+1 fish is downstream of i fish, if a fish is going upstream from a earlier position, it will encounter this fish            
            //this upstream fish will attempt to eat all the downstream fish until no more fish are left or it is eaten by a bigger fish
            while (!fish_downstream.empty()) {
                if (fish_downstream.top() > A[i]) break;
                else fish_downstream.pop();
            }
            //if no more fish are left, this fish has survived
            if (fish_downstream.empty()) fish_alive++;
        }
    }
    //all the fish going downstream will survive
    return fish_alive + fish_downstream.size();
}

int main () {
    vector<int> A = {4,3,2,1,5};
    vector<int> B = {0,1,0,0,0};
    test(solution(A,B), 2);
    return 0;
}
