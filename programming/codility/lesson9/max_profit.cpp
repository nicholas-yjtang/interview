#include <vector>
#include <iostream>
#include "common.h"

using namespace std;

int solution (vector<int> &A) {
    if (A.size() == 0) return 0;
    vector <int> max_profit(A.size(), 0);
    int min_price = A[0];
    int max_profit_so_far = 0;
    //max profit is calculated by selling the stock at the current day
    //and buying it at the day with the lowest price
    //we only need to take note of when the lowest price was seen before selling on that particular day
    for (int i = 1; i < (int)A.size(); i++) {
        if (A[i] < min_price) min_price = A[i];
        int profit = A[i] - min_price;
        max_profit[i] = profit;
        if (profit > max_profit_so_far) max_profit_so_far = profit;
    }
    return max_profit_so_far;
}

int main () {
    vector<int> A = {23171,21011,21123,21366,21013,21367};
    test(solution(A), 356);
    A = {};
    test(solution(A), 0);
    return 0;
}