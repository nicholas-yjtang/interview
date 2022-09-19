#include "transmission.h"
#include <iostream>
#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;

LoggerPtr transmissionLogger (Logger::getLogger("transmission"));

Transmission::Transmission() {

}

Transmission::~Transmission() {

}

int Transmission::getInfectedTime(int row, int column, int ** patient_wards) {    
    if (row <=0) return -1;
    if (column <=0) return -1;
    if (patient_wards == NULL) return -1;
    queue<Transmission::ward> current_infected;
    queue<Transmission::ward> newly_infected;
    initializeInfected(row, column, patient_wards, current_infected);
    if (current_infected.empty()) return -1;
    int current_time = 0;
    while (!current_infected.empty()) {
        LOG4CXX_DEBUG(transmissionLogger, "step " << current_time);
        infect(row, column,patient_wards, current_infected, newly_infected);    
        if (newly_infected.empty()) break;
        current_infected.swap(newly_infected);    
        current_time++;
    }
    if (isFullyInfected(row, column, patient_wards)) return current_time;
    return -1;
}

void Transmission::initializeInfected(int row, int column, int ** ward, queue<Transmission::ward> & infected) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (ward[i][j] == 2) infected.push({i,j});            
        }
    }
}
bool Transmission::isFullyInfected(int row, int column, int ** ward) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (ward[i][j] == 1) return false;
        }
    }    
    return true;
}

void Transmission::infect(int row, int column, int ** patient_wards, queue<Transmission::ward> &current_infected, queue<Transmission::ward> &newly_infected) {
    while (!current_infected.empty()) {
        Transmission::ward current_ward = current_infected.front();
        LOG4CXX_DEBUG(transmissionLogger, "currently infected ward[" << current_ward.row << "][" << current_ward.column <<"]");
        current_infected.pop();
        infectUp(current_ward.row, current_ward.column, row, column, patient_wards, newly_infected);
        infectDown(current_ward.row, current_ward.column, row, column, patient_wards, newly_infected);
        infectLeft(current_ward.row, current_ward.column, row, column, patient_wards, newly_infected);
        infectRight(current_ward.row, current_ward.column, row, column, patient_wards, newly_infected);
    }
}
void Transmission::infect(int current_row, int current_column, int patient_wards_row, int patient_wards_column, int ** patient_wards, queue<Transmission::ward> & infected) {
    if (current_row <0) return;
    if (current_column< 0) return;
    if (current_row>=patient_wards_row) return;
    if (current_column >= patient_wards_column) return;
    if (isUninfected(current_row,current_column,patient_wards)) {
        patient_wards[current_row][current_column] = 2;
        LOG4CXX_DEBUG(transmissionLogger, "ward[" << current_row << "][" << current_column << "] is infected");
        infected.push({current_row, current_column});
    }
}

void Transmission::infectUp(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** patient_wards, queue<Transmission::ward> & infected) {
    if (isInfected(current_row, current_column,patient_wards)) infect(current_row-1, current_column,patient_wards_row, patient_wards_column, patient_wards, infected);
}

void Transmission::infectDown(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** patient_wards, queue<Transmission::ward> & infected) {
    if (isInfected(current_row, current_column,patient_wards)) infect(current_row+1, current_column,patient_wards_row, patient_wards_column, patient_wards, infected);

}

void Transmission::infectLeft(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** patient_wards, queue<Transmission::ward> & infected) {
    if (isInfected(current_row, current_column,patient_wards)) infect(current_row, current_column-1,patient_wards_row, patient_wards_column, patient_wards, infected);

}

void Transmission::infectRight(int current_row, int current_column, int patient_wards_row, int patient_wards_column, int ** patient_wards, queue<Transmission::ward> & infected) {
    if (isInfected(current_row, current_column,patient_wards)) infect(current_row, current_column+1,patient_wards_row, patient_wards_column, patient_wards, infected);
}

bool Transmission::isInfected(int current_row, int current_column, int ** patient_wards) {
    if (patient_wards[current_row][current_column] == 2) return true;
    return false;
}

bool Transmission::isUninfected(int current_row, int current_column, int ** patient_wards) {
    if (patient_wards[current_row][current_column] == 1) return true;
    return false;
}