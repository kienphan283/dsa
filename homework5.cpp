#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void findNearestNeighbors(Point points[], int n, Point target, int k) {
    float distances[n];
    for (int i = 0; i < n; i++) {
        distances[i] = distance(points[i], target);
    }
    
    for (int i = 0; i < k; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (distances[j] < distances[minIndex]) {
                minIndex = j;
            }
        }
        swap(distances[i], distances[minIndex]);
        swap(points[i], points[minIndex]);
    }

    cout << "Các điểm gần nhất là:" << endl;
    for (int i = 0; i < k; i++) {
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
    }
}

int main() {
    Point points[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {2, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    Point target = {2, 2};
    int k = 3;
    findNearestNeighbors(points, n, target, k);
    return 0;
}
