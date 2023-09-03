#include <iostream>
#include <vector>
#include <math.h>
#include "common.h"

using namespace std;

float average(int sum, int num_of_elements) {
    return sum/(float)num_of_elements;
}

int solution (vector<int>&A) {
    if (A.size() <2) return 0;
    int min_sum = (A[0]+A[1]);
    int min_sum_num_of_elements = 2;
    int min_sum_pos = 0;
    if (A.size() == 2) return min_sum_pos;
    int current_sum = min_sum;
    int current_num_of_elements = min_sum_num_of_elements;
    for (int i = 2; i < (int)A.size(); i++) {
        // To decide if we should include the current element to the average 
        // This current element should be smaller than the current average
        // Otherwise there is no reason to include this particular element
        // The second factor to decide is to see if the previous element is bigger than the current average
        // Because a smaller average can be obtained via a positive between 2 negative numbers, for example -100, 1, -200
        if (A[i] < average(current_sum, current_num_of_elements)
            && A[i-1] > average(current_sum, current_num_of_elements)
        ) {
            current_sum += A[i];
            current_num_of_elements++;
        }
        else {
            // since this is no longer a candidate for the smaller average
            // we can check if the current average is smaller than the previous minimum average
            // we can also set the new current average to be the current element, and the previous element
            if (average(current_sum, current_num_of_elements) < average(min_sum, min_sum_num_of_elements)) {
                min_sum = current_sum;                
                min_sum_num_of_elements = current_num_of_elements;
                min_sum_pos = i-current_num_of_elements;
            }
            current_sum = A[i-1]+A[i];
            current_num_of_elements = 2;
        }
    }
    //final check on the last elements
    if (average(current_sum, current_num_of_elements) < average(min_sum, min_sum_num_of_elements)) {
        min_sum = current_sum;                
        min_sum_num_of_elements = current_num_of_elements;
        min_sum_pos = A.size()-current_num_of_elements;
    }
    return min_sum_pos;

}

int main () {
    vector<int> A = {4,2,2,5,1,5,8};
    test (solution(A), 1);
    A = {4,2,2,-1000,1,-1000,8};
    test (solution(A), 3);
    A = {1,2};
    test (solution(A), 0);
    A = {1,0,0,0,0,0,0,0,0,0,0,0,0,0};
    test (solution(A), 1);
    A = {1,0,0,0,0,0,0,0,0,0,0,0,0,-1};
    test (solution(A), 12);
    return 0;
}