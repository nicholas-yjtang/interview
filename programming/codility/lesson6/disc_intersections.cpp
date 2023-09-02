#include <vector>
#include <iostream>
#include <algorithm>
#include "common.h"

using namespace std;

struct Point {
    long position;
    int type;
    Point(long position, int type) : position(position), type(type) {}
};

bool compare_points (Point a, Point b) {
    if (a.position == b.position) {
        return a.type < b.type;
    }
    return a.position < b.position;
}

// Notice that if we add all the ends of the circle as an array of points
// We can easily calculate the number of intersections by counting how many left parts of the circle are before the right side of the circle
// Because any left part of a circle that is before the right part of another circle, we can simply conclude it must intersect with this right part of the circle
// The important part is we need to be able to sort the ends of the circles

int solution(vector<int> &A) {
    vector<Point> points;
    for (int i = 0; i < (int)A.size(); i++) {
        points.push_back(Point((long)i-A[i], 0)); //left side of the circle
        points.push_back(Point((long)i+A[i], 1)); //right side of the circle
    }
    sort(points.begin(), points.end(), compare_points);
    int intersections = 0;
    int active_circles = 0;
    for (int i = 0; i < (int)points.size(); i++) {
        if (points[i].type == 0) { //left side of the circle, keep adding until we encounter the right side of the circle
            intersections += active_circles; 
            active_circles++;
        }
        else { //right side of the circle, we remove this from the active list
            active_circles--;
        }
        if (intersections > 10000000) return -1;
    }
    return intersections;
}

int naive_solution(vector <int> &A) {
    int intersections = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = i+1; j < (int)A.size(); j++) {
            if ((long)i + A[i] >= (long)j - A[j]) {
                intersections++;
                if (intersections > 10000000) return -1;
            }
        }
    }
    return intersections;
}

int main () {
    vector<int> A = {1,5,2,1,4,0};
    test(A);
    A = {1, 2147483647, 0};
    test(A);
    return 0;
}