#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        cout << "Comparing " << arr[j] << " with pivot " << pivot << endl;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

int findKthSmallest(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int index = partition(arr, low, high);
        cout << "Partition at index " << index << ": " << arr[index] << endl;

        if (index - low == k - 1) return arr[index];
        if (index - low > k - 1)
            return findKthSmallest(arr, low, index - 1, k);

        return findKthSmallest(arr, index + 1, high, k - index + low - 1);
    }
    return -1;
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 4, 26, 13};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    int result = findKthSmallest(arr, 0, size - 1, k);
    if (result == -1)
        cout << "k is out of bounds" << endl;
    else
        cout << "The " << k << "-th smallest element is: " << result << endl;

    return 0;
}
