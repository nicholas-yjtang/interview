#ifndef WARD_FACTORY_H
#define WARD_FACTORY_H
#include <string>
using namespace std;

class WardFactory {
    public:        
        static int ** create_ward(int row, int column);
        static void free_wards(int ** patient_wards, int row, int column);
        static string printWards(int row, int column, int** patient_wards);
};

#endif