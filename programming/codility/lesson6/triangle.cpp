#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution (vector<int> &A) {
    //make the observation that we need to only check
    //A[i] + A[j] > A[k] for all i < j < k
    //if A[i] + A[j] > A[k] then A[i] + A[k] > A[j] because A[k] > A[j], so the sum on the left side would always be larger by including the larger number
    //and A[j] + A[k] > A[i] because A[j] > A[i], so the sum on the left side will always be larger by including the larger number
    //now consider the case where i, j, k are not in sequence, ie, i < j-1, j < k-1
    //suppose we have proven this particular case where A[i] + A[j] > A[k]. Take a specific example where i = 0, j = 2, k = 4
    //since A[1] > A[0], A[1] + A[2] > A[4], and since A[3] > A[1], A[3] + A[2] > A[4], ie i=k-2, j=k-1
    //so if there exists a case where A[i] + A[j] > A[k], then we only need to check i = k-2, j = k-1
    //to put it in another format, check A[i] + A[i+1] > A[i+2]
    sort(A.begin(), A.end());
    for (int i = 0; i < (int)A.size()-2; i++) {
        if ((long)A[i] + A[i+1] > A[i+2]) return 1;
    }
    return 0;
}

int main () {
    vector<int> A = {10,2,5,1,8,20};
    cout << solution(A) << endl;
    A = {10,50,5,1};
    cout << solution(A) << endl;
    A = {10,50,5,1};
    cout << solution(A) << endl;
    A = {2147483647,2147483647,2147483647};
    cout << solution(A) << endl;
    return 0;
}