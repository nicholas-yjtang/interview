#include <vector>
#include <iostream>
#include "common.h"

using namespace std;

int solution(vector<int> &A) {
    vector<int> max_ending_left(A.size()); //place the current max ending at i, A[X+1]...A[Y-1]
    vector<int> max_ending_left_index(A.size()); //place the starting index of the current max ending at i
    vector<int> max_ending_right(A.size()); //place the current max ending at i, from the right sde, A[Y+1]...A[Z-1]
    vector<int> max_ending_right_index(A.size()); //place the ending index of the current max ending at i
    int current_max = 0;
    for (int i = 1; i < (int)A.size()-2; i++) {
        //if the current max is negative despite adding A[i], then we start a new max ending at i
        if (A[i]+current_max < 0) {
            current_max = 0;
            max_ending_left_index[i] = i;
        }
        else {
            current_max = current_max + A[i];
            max_ending_left_index[i] = max_ending_left_index[i-1];
        } 
        max_ending_left[i] = current_max;
    }
    print_vector(max_ending_left);
    print_vector(max_ending_left_index);
    current_max = 0;
    max_ending_right_index[(int)A.size()-1] = (int)A.size()-1;
    for (int i = (int)A.size()-2; i > 1; i--) {
        //if the current max is negative despite adding A[i], then we start a new max ending at i
        if (A[i]+current_max < 0) {
            current_max = 0;
            max_ending_right_index[i] = i;            
        }       
        else {
            current_max = current_max + A[i];
            max_ending_right_index[i] = max_ending_right_index[i+1];
        }
        max_ending_right[i] = current_max;
    }
    print_vector(max_ending_right);    
    print_vector(max_ending_right_index);
    int max_double_slice = 0;
    for (int i = 1; i < (int)A.size()-1; i++) {
        int current_double_slice = max_ending_left[i-1]+max_ending_right[i+1];
        print_slice(max_ending_left_index, max_ending_right_index, i, current_double_slice);
        max_double_slice = max(max_double_slice, current_double_slice); //max double slice is the max of all double slices, left and right at position i
    }
    return max_double_slice;
}

int main () {
    vector<int> A = {3,2,6,-1,4,5,-1,2};
    test(solution(A), 17);
    A = {5,17,0,3};
    test(solution(A), 17);
    A = {0,10,-5,-2,0};
    test(solution(A), 10);
    A = {1,2,3,4,5,6,7,8,9,10};
    test(solution(A), 42);
    A = {-8, 10, 20, -5, -7, -4};
    test(solution(A), 30);
    A = {-8, -9,-10, -11, -12, 10, 20, -5, -7, -4};
    test(solution(A), 30);
    A = {-8, -7,-6, -5, -4, 10, 20, -5, -7, -4};
    test(solution(A), 30);
    A = {-8, -9,-10, -11};
    test(solution(A), 0);    
    return 0;
}