#include <iostream>
#include <string>
using namespace std;

int interpolationSearch(string arr[], int size, string target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        // Tính chỉ số giữa như cách Binary Search
        int pos = left + (right - left) / 2;

        cout << "Checking index " << pos << ": " << arr[pos] << endl;

        // So sánh chuỗi tại `pos` với `target`
        if (arr[pos] == target) {
            return pos;  // Tìm thấy `target`, trả về chỉ số
        } else if (arr[pos] < target) {
            left = pos + 1;  // Tìm kiếm ở nửa bên phải
        } else {
            right = pos - 1; // Tìm kiếm ở nửa bên trái
        }
    }

    return -1;  // Không tìm thấy `target`
}

int main() {
    string arr[] = {"apple", "banana", "cherry", "date", "fig", "grape"};
    int size = sizeof(arr) / sizeof(arr[0]);
    string target = "date";

    int result = interpolationSearch(arr, size, target);
    if (result == -1) {
        cout << "Element not found" << endl;
    } else {
        cout << "Element found at index " << result << endl;
    }

    return 0;
}
