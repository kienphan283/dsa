#include <iostream>
using namespace std;

int findMissingNumber(int arr[], int size) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        cout << "Checking index " << mid << " with value " << arr[mid] << endl;

        if (arr[mid] != mid) {
            // Nếu phần tử tại `mid` không khớp với chỉ số `mid`
            if (mid == 0 || arr[mid - 1] == mid - 1) {
                cout << "Missing number found: " << mid << endl;
                return mid;
            }
            right = mid - 1; // Thu hẹp phạm vi tìm kiếm sang trái
        } else {
            left = mid + 1; // Thu hẹp phạm vi tìm kiếm sang phải
        }
    }

    // Nếu không tìm thấy số nào bị thiếu trong khoảng từ 0 đến size - 1
    cout << "No missing number in range 0 to " << size - 1 << ", missing number is " << size << endl;
    return size;
}

int main() {
    int arr[] = {0, 1, 2, 3, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Missing number is: " << findMissingNumber(arr, size) << endl;
    return 0;
}
