#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int linearSearch(int arr[], int size, int target) {
    cout << "Starting Linear Search...\n";
    for (int i = 0; i < size; i++) {
        cout << "Checking index " << i << ": " << arr[i] << endl;
        if (arr[i] == target) return i;
    }
    return -1;
}

int binarySearch(int arr[], int size, int target) {
    cout << "Starting Binary Search...\n";
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        cout << "Checking index " << mid << ": " << arr[mid] << endl;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int jumpSearch(int arr[], int size, int target) {
    cout << "Starting Jump Search...\n";
    int step = static_cast<int>(sqrt(size));
    int prev = 0;

    while (arr[min(step, size) - 1] < target) {
        cout << "Jumping to index " << step - 1 << ": " << arr[min(step, size) - 1] << endl;
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;
    }

    cout << "Performing Linear Search from index " << prev << " to " << min(step, size) - 1 << endl;
    for (int i = prev; i < min(step, size); i++) {
        cout << "Checking index " << i << ": " << arr[i] << endl;
        if (arr[i] == target) return i;
    }
    return -1;
}

void measureSearch(int (*searchFunc)(int[], int, int), int arr[], int size, int target, const string &searchType) {
    clock_t start = clock();
    int result = searchFunc(arr, size, target);
    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    cout << searchType << " Search: ";
    if (result == -1) 
        cout << "Element not found. ";
    else 
        cout << "Element found at index " << result << ". ";
    cout << "Time taken: " << duration << " ms.\n" << endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Sample sorted array
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;  // Target element to search for

    measureSearch(linearSearch, arr, size, target, "Linear");
    measureSearch(binarySearch, arr, size, target, "Binary");
    measureSearch(jumpSearch, arr, size, target, "Jump");

    return 0;
}
