#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

int solution (vector <int> & A) {
    int total_sum = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        total_sum += A[i];
    }
    int min_difference = abs(A[0] - (total_sum - A[0])); //set the initial min difference to be the first element
    int current_sum = 0;
    for (int i = 0; i < (int)A.size()-1; i++) {
        current_sum += A[i];
        int current_difference = abs(current_sum - (total_sum - current_sum));
        if ( current_difference< min_difference) {
            min_difference = current_difference;
        }        
    }
    return min_difference;
}

int main() {
    vector<int> A = {3,1,2,4,3};
    test(solution(A), 1);
    A = {-1000,1000};
    test(solution(A), 2000);

}