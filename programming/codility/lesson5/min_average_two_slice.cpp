#include <iostream>
#include <vector>
#include <math.h>

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
        if (A[i] < average(current_sum, current_num_of_elements)
            && A[i-1] > average(current_sum, current_num_of_elements)
        ) {
            current_sum += A[i];
            current_num_of_elements++;
        }
        else {
            if (average(current_sum, current_num_of_elements) < average(min_sum, min_sum_num_of_elements)) {
                min_sum = current_sum;                
                min_sum_num_of_elements = current_num_of_elements;
                min_sum_pos = i-current_num_of_elements;
            }
            //cout << "current_avg:" << average(current_sum, current_num_of_elements)<< ", pos: " << i-current_num_of_elements << "," << i-1 << endl;
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
    //cout << "min_avg: " << average(min_sum, min_sum_num_of_elements) << endl;
    return min_sum_pos;

}

int main () {
    vector<int> A = {4,2,2,5,1,5,8};
    cout << solution(A) << endl;
    A = {4,2,2,-1000,1,-1000,8};
    cout << solution(A) << endl;
    A = {1,2};
    cout << solution(A) << endl;
    A = {1,0,0,0,0,0,0,0,0,0,0,0,0,0};
    cout << solution(A) << endl;    
    A = {1,0,0,0,0,0,0,0,0,0,0,0,0,-1};
    cout << solution(A) << endl;  
    return 0;
}