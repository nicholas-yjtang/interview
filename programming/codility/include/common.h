#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>

using namespace std;

bool debug = true;

int solution(vector<int> &A);
int naive_solution(vector<int> &A);

void print_vector (vector<int> &A) {
    if (!debug) return;
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void test(vector<int> &A) {

    print_vector(A);
    time_t start, end;
    double time_taken;
    start = clock();
    int result = solution(A);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Solution time taken: " << time_taken << " seconds" << endl;
    start = clock();
    int naive_result = naive_solution(A);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Naive solution time taken: " << time_taken << " seconds" << endl;
    if (result != naive_result) {
        cout << "Error: result=" << result << " naive_result=" << naive_result << endl;
    }
    else {
        cout << "OK" << endl;
    }
}

#endif