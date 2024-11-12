#include <iostream>
using namespace std;

int binarySearchFirst(int arr[], int size, int target) {
    int left = 0, right = size - 1, result = -1;
    cout << "Searching for the first occurrence of " << target << ":\n";
    while (left <= right) {
        int mid = left + (right - left) / 2;
        cout << "Checking index " << mid << " with value " << arr[mid] << endl;
        if (arr[mid] == target) {
            result = mid;
            cout << "Found target at index " << mid << ", moving left to find first occurrence.\n";
            right = mid - 1;
        } else if (arr[mid] < target) {
            cout << "Value at mid is less than target, moving right.\n";
            left = mid + 1;
        } else {
            cout << "Value at mid is greater than target, moving left.\n";
            right = mid - 1;
        }
    }
    return result;
}

int binarySearchLast(int arr[], int size, int target) {
    int left = 0, right = size - 1, result = -1;
    cout << "\nSearching for the last occurrence of " << target << ":\n";
    while (left <= right) {
        int mid = left + (right - left) / 2;
        cout << "Checking index " << mid << " with value " << arr[mid] << endl;
        if (arr[mid] == target) {
            result = mid;
            cout << "Found target at index " << mid << ", moving right to find last occurrence.\n";
            left = mid + 1;
        } else if (arr[mid] < target) {
            cout << "Value at mid is less than target, moving right.\n";
            left = mid + 1;
        } else {
            cout << "Value at mid is greater than target, moving left.\n";
            right = mid - 1;
        }
    }
    return result;
}

int countOccurrences(int arr[], int size, int target) {
    int first = binarySearchFirst(arr, size, target);
    if (first == -1) return 0;  // If the element is not found at all
    int last = binarySearchLast(arr, size, target);
    return last - first + 1;  // Total count of occurrences
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    
    cout << "Count of " << target << " is: " << countOccurrences(arr, size, target) << endl;
    return 0;
}
