#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<int> &A) {
    unordered_map<int,int> numbers;
    //just add all numbers to the map, the number of unique numbers is the size of the map
    //the alternative to "sort" will be slower O(nlogn) vs O(n)
    for (int i = 0; i < (int)A.size(); i++) {
        numbers[A[i]]++;
    }
    return (int)numbers.size();
}

int main () {
    vector<int> A = {2,1,1,2,3,1};
    cout << solution(A) << endl;
    return 0;
}