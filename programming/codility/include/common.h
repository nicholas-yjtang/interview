#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>

using namespace std;

bool debug = true;

void print_vector (vector<int> &A) {
    if (!debug) return;
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void print_slice(vector<int> max_ending_left_index, vector<int> max_ending_right_index, int i, int current_double_slice) {
    cout << "(" << max_ending_left_index[i-1] << "," << i << "," << max_ending_right_index[i+1] << ")=" <<  current_double_slice << endl;
}

void test(vector<int> &A, int (*solution)(vector<int>&), int (*naive_solution)(vector<int>&)) {

    time_t start, end;
    start = clock();
    int result = solution(A);
    end = clock();
    double solution_time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    int naive_result = naive_solution(A);
    end = clock();
    double naive_time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    double difference = (solution_time_taken > naive_time_taken) ? solution_time_taken - naive_time_taken : naive_time_taken - solution_time_taken;
    string compare_time = (solution_time_taken > naive_time_taken) ? "slower by " : "faster by ";
    if (result != naive_result) {
        if (debug) print_vector(A);
        cout << "Error: result=" << result << " expected_result=" << naive_result << ", solution is " << compare_time << difference << endl;
        
    }
    else {
        cout << "OK, solution is " << compare_time << difference << endl;
    }
}

void test (int result, int expected_result) {
    if (result != expected_result) {
        cout << "Error: result=" << result << " expected_result=" << expected_result << endl;
    }
    else {
        cout << "OK" << endl;
    }
}

void test(vector<int> results, vector<int> expected_results) {
    if (results.size() != expected_results.size()) {
        cout << "Error: result size=" << results.size() << " expected_result size=" << expected_results.size() << endl;
        return;
    }
    for (int i = 0; i < (int)results.size() &&  i < (int) expected_results.size(); i++) {
        if (results[i] != expected_results[i]) {
            cout << "Error: result[" << i << "]=" << results[i] << " expected_result[" << i << "]=" << expected_results[i] << endl;
        }
    }
    cout << "OK" << endl;
}
#endif