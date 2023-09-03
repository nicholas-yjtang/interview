#include <iostream>
#include <vector>
#include <string>
#include "common.h"

using namespace std;

vector<int> solution (string & S, vector<int> &P, vector<int> &Q) {
    int N = (int)S.size();
    int M = (int)P.size();
    vector<int> A(N+1,0);
    vector<int> C(N+1,0);
    vector<int> G(N+1,0);
    vector<int> T(N+1,0);
    for (int i = 0; i < N; i++) {
        if (S[i] == 'A') A[i+1] = A[i] + 1;
        else A[i+1] = A[i];
        if (S[i] == 'C') C[i+1] = C[i] + 1;
        else C[i+1] = C[i];
        if (S[i] == 'G') G[i+1] = G[i] + 1;
        else G[i+1] = G[i];
        if (S[i] == 'T') T[i+1] = T[i] + 1;
        else T[i+1] = T[i];
    }
    vector<int> result(M,0);
    for (int i = 0; i < M; i++) {
        if (A[Q[i]+1] - A[P[i]] > 0) result[i] = 1;
        else if (C[Q[i]+1] - C[P[i]] > 0) result[i] = 2;
        else if (G[Q[i]+1] - G[P[i]] > 0) result[i] = 3;
        else if (T[Q[i]+1] - T[P[i]] > 0) result[i] = 4;
    }
    return result;
}

void print_result(vector<int> &result) {
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << ",";
    }
    cout << endl;
}
int main() {
    string S = "CAGCCTA";
    vector<int> P = {2,5,0};
    vector<int> Q = {4,5,6};
    test (solution(S,P,Q), {2,4,1});    
}