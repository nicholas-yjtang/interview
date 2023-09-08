#include<iostream>
#include<vector>
#include<string>
#include <memory>

using namespace std;

class Number {
    public:
    Number() : theNum(0) { }
    ~Number() {
        delete theNum; 
    }

    void set(int* t) {
        theNum = t;
    }

    int get(void) {
        return *theNum;
    }

    private:
    int* theNum;
};

unique_ptr<Number> createNumber(int i) {
    Number* ret = new Number;
    ret->set(new int(i));
    return unique_ptr<Number>(ret);
}


string display_number(vector<unique_ptr<Number>> & position, bool isAscii) {

    string display = "";
    for(int i = 0; i < (int)position.size(); i++) {
        for(int j = 0; j <= i; j++) {
            char c = (j < i ) ? ',' : '\n';
            if (isAscii) display += (char)(position[j]->get() + 65);
            else display += to_string(position[j]->get());
            display += c;
        }
    }
    return display;
}


const int numSize = 10;
int main(int argc, char** argv) {

    vector<unique_ptr<Number>> position;
    // initialize createNumber with 0 to 10
    for(int i = 0; i <= numSize; i++) {
        position.push_back(createNumber(i));
    }
    
    cout << display_number(position, false) << endl;
    cout << display_number(position, true) << endl;

    return 0;
}