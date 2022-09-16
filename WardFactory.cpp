#include "WardFactory.h"

int ** WardFactory::create_ward(int row, int column) {
    int ** wards = new int*[row];
    for (int i = 0; i < row; i++) {
        wards[i] = new int [column];
    }    
    return wards;
}

void WardFactory::free_wards(int ** patient_wards, int row, int column) {
    for (int i = 0; i < row; i++) {
        delete [] patient_wards[i];
    }
    delete [] patient_wards;
}

string WardFactory::printWards(int row, int column, int** patient_wards) {
    string wards = "";
    for (int i = 0; i < row; i++) {                
        for (int j = 0; j < column; j++) {
            wards += to_string(patient_wards[i][j]) + " ";
        }
        wards += '\n';
    }
    wards.pop_back();
    return wards;
}