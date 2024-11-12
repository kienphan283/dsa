#include <iostream>
using namespace std;

int bidirectionalBinarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        if (arr[left] == target) return left;
        if (arr[right] == target) return right;

        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }

        left++;
        right--;
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 6;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = bidirectionalBinarySearch(arr, n, target);
    if (result != -1)
        cout << "Phần tử tìm thấy tại chỉ số: " << result << endl;
    else
        cout << "Phần tử không tìm thấy" << endl;
    return 0;
}
