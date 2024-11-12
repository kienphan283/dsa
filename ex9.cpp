#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

struct Point {
    int x, y;
};

float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float findClosestPair(Point points[], int n) {
    float minDist = numeric_limits<float>::max();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float dist = distance(points[i], points[j]);
            if (dist < minDist) minDist = dist;
        }
    }
    return minDist;
}

int main() {
    Point points[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(points) / sizeof(points[0]);
    float minDist = findClosestPair(points, n);
    cout << "Khoảng cách gần nhất giữa hai điểm là: " << minDist << endl;
    return 0;
}
