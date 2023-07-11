#include<iostream>
#include<vector>

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

Number* createNumber(int i) {
    Number* ret = new Number;
    ret->set(new int(i));
    return ret;
}

const int numSize = 10;
int main(int argc, char** argv) {
    using namespace std;
    vector<Number*> position;

    // initialize createNumber with 0 to 10
    for(int i = 0; i <= numSize; i++) {
        position.push_back(createNumber(i));
    }
    
    // retrieve and display "0,1,2,3,4,5,6,7,8,9,10"
    for(int i = 0; i <= numSize; i++) {
        for(int j = 0; j <= i; j++) {
            char c = (j < i ) ? ',' : '\n';
            cout << position[j]->get() << c;
        }
    }
    cout << endl;

    // clean up
    for(int i = 0; i < numSize; i++) {
        delete position[i];
    }
    return 0;
}