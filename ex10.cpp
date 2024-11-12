#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int searchWithExponentialBackoff(int arr[], int n, int target) {
    int attempt = 0;
    while (attempt < n) {
        if (arr[attempt] == target) return attempt;
        attempt++;
        int delay = pow(2, attempt);
        cout << "Đợi " << delay << " giây...\n";
        time_t start = time(0);
        while (time(0) < start + delay); // Chờ delay giây
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 5;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = searchWithExponentialBackoff(arr, n, target);
    if (result != -1)
        cout << "Phần tử tìm thấy tại chỉ số: " << result << endl;
    else
        cout << "Phần tử không tìm thấy" << endl;
    return 0;
}
