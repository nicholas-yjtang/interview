#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include <queue>
using namespace std;

class Transmission {
    public:
        Transmission();
        virtual ~Transmission();
        struct ward {
            int row;
            int column;
        };        
        int getInfectedTime(int row, int column, int ** ward);
        void initializeInfected(int row, int column, int ** ward, queue<Transmission::ward> & infected);
        void infectUp(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** ward, queue<Transmission::ward> & infected);
        void infectDown(int current_row, int current_column,int patient_wards_row, int patient_wards_column, int ** ward, queue<Transmission::ward> & infected);
        void infectLeft(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** ward, queue<Transmission::ward> & infected);
        void infectRight(int current_row, int current_column, int patient_wards_row, int patient_wards_column,int ** ward, queue<Transmission::ward> & infected);
        void infect(int current_row, int current_column, int patient_wards_row, int patient_wards_column, int ** patient_wards, queue<Transmission::ward> & infected);
        void infect(int row, int column, int ** patient_wards, queue<Transmission::ward> &current_infected, queue<Transmission::ward>& newly_infected);
        bool isFullyInfected(int row, int column, int ** patient_wards);

};
#endif