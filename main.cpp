#include "transmission.h"
#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc <=1) return 1;
    ifstream file;
    string line;
    file.open(argv[1]);
    if (file.is_open()) {        
        unique_ptr<Transmission> transmission = make_unique<Transmission> ();

        while(!file.eof()) {
            getline(file, line);
            int delimiter_index = line.find(" ");
            int row = stoi(line.substr(0, delimiter_index));
            int column = stoi(line.substr(delimiter_index+1, string::npos));
            int ** patient_wards = new int*[row];
            for (int i = 0; i < row; i++) {
                patient_wards[i] = new int[column];
                getline(file,line);                
                stringstream tokenizer (line);
                string token;
                for (int j = 0; j < column; j++) {
                    getline(tokenizer, token, ' ');
                    patient_wards[i][j] = stoi(token);
                }
            }
            cout << "row:" << row << "column:" << column << endl;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    cout << patient_wards[i][j] << " ";
                }
                cout << endl;
            }
            cout << transmission->getInfectedTime(row, column, patient_wards) << endl;

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    cout << patient_wards[i][j] << " ";
                }
                cout << endl;              
            }  
            for (int i = 0; i < row; i++) {
                delete [] patient_wards[i];
            }
            delete [] patient_wards;
        }
        file.close();
    }


}