#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>

using namespace std;

void print_vector (vector<int> &A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

#endif