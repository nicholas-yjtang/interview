#include <iostream>
#include <vector>

using namespace std;

vector<int> solution(vector<int> &A, int K) {
    vector<int> B(A.size());
    for (int i = 0; i < (int)A.size(); i++) {
        B[(i+K)%A.size()] = A[i]; //simple mod operation on the index, no need to actually "shift"
    }
    return B;
}

int main () {
    vector<int> A = {3,8,9,7,6};
    vector<int> B = solution(A, 3);
    for (int i = 0; i < (int)B.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    return 0;
}