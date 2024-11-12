#include <iostream>
#include <cmath>
using namespace std;

int jumpSearch(int arr[], int size, int target, int stepSize) {
    int step = stepSize;
    int prev = 0;

    while (arr[min(step, size) - 1] < target) {
        cout << "Jumping to index " << step - 1 << ": " << arr[min(step, size) - 1] << endl;
        prev = step;
        step += stepSize;
        if (prev >= size) return -1;
    }

    cout << "Linear search from index " << prev << " to " << min(step, size) - 1 << endl;
    for (int i = prev; i < min(step, size); i++) {
        cout << "Checking index " << i << ": " << arr[i] << endl;
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    int stepSize = 2;
    int result = jumpSearch(arr, size, target, stepSize);
    if (result == -1)
        cout << "Element not found" << endl;
    else
        cout << "Element found at index " << result << endl;
    return 0;
}
