#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int solution (vector<int> &A) {
    unordered_map<int,int> numbers;
    for (int i = 0; i < (int)A.size(); i++) {
        numbers[A[i]]++;
    }
    for (int i = 1; i <= (int)A.size()+1; i++) {
        if (numbers[i] == 0) return i;
    }
    return 1;

}

int main () {
    vector<int> A = {2,3,1,5};
    cout << solution(A) << endl;    
    A = {-1000,-3,1,3};
    cout << solution(A) << endl;    
    A = {-1000};
    cout << solution(A) << endl;      
    A = {};
    cout << solution(A) << endl;          
    return 0;
}