#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<int> &A) {
    unordered_map<int,int> numbers;
    //ignore negative numbers
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] > 0) numbers[A[i]]++;
    }

    //start checking from 1 until the size of the array
    for (int i = 1; i <= (int)A.size(); i++) {
        if (numbers[i]==0) return i;
    }
    return (int)A.size()+1;

}

int main () {
    vector<int> A = {1,3,6,4,1,2};
    cout << solution(A) << endl;
    A = {1,2,3};
    cout << solution(A) << endl;
    A = {-1,-3};
    cout << solution(A) << endl;
}