#include <iostream>
#include <vector>
#include <stack>
#include "common.h"

using namespace std;

int solution(vector <int> &H) {
    stack<int> blocks;
    int count = 0;
    for (int i = 0; i < (int)H.size(); i++) {
        // Remove all blocks that are higher than the current height
        while (!blocks.empty() && blocks.top() > H[i]) {
            blocks.pop();
        }
        // If the stack is empty or the top block is lower than the current height, we add a new one
        if (blocks.empty() || blocks.top() < H[i]) {
            blocks.push(H[i]);
            count++;
        }
    }
    return count;
}

int main () {
    vector<int> H = {8,8,5,7,9,8,7,4,8};
    test(solution(H), 7);
    return 0;
}