#include "transmission.h"
#include "WardFactory.h"
#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

using namespace std;
using namespace log4cxx;

LoggerPtr mainlogger (Logger::getLogger("main"));



int main(int argc, char** argv) {
    if (argc <=1) return 1;
    PropertyConfigurator::configure("conf/log4j.properties");
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
            auto custom_deleter = [row,column] (int** t) {WardFactory::free_wards(t,row,column);};
            unique_ptr<int*, decltype(custom_deleter)> patient_wards (WardFactory::create_ward(row, column), custom_deleter);
            for (int i = 0; i < row; i++) {
                getline(file,line);                
                stringstream tokenizer (line);
                string token;
                for (int j = 0; j < column; j++) {
                    getline(tokenizer, token, ' ');
                    if (!token.empty()) (patient_wards.get())[i][j] = stoi(token);
                    else (patient_wards.get())[i][j] = 0;
                }
            }
            LOG4CXX_DEBUG(mainlogger, "original ward\n" << WardFactory::printWards(row, column, patient_wards.get()));
            cout << transmission->getInfectedTime(row, column, patient_wards.get()) << endl;
            LOG4CXX_DEBUG(mainlogger, "after infection ward\n" << WardFactory::printWards(row, column, patient_wards.get()));
        }
        file.close();
    }


}