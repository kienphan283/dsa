#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void updatePrices(int prices[], int n) {
    for (int i = 0; i < n; i++) {
        prices[i] = rand() % 100 + 1;  // Giá trị ngẫu nhiên từ 1 đến 100
    }
}

int searchPrice(int prices[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (prices[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    srand(time(0));
    const int n = 10;
    int prices[n];
    
    // Cập nhật giá trị lần đầu
    updatePrices(prices, n);
    
    int target = 50;
    int result = searchPrice(prices, n, target);
    if (result != -1) {
        cout << "Giá " << target << " tìm thấy tại chỉ số: " << result << endl;
    } else {
        cout << "Giá " << target << " không tìm thấy, cập nhật lại dữ liệu và tìm kiếm lại..." << endl;
        
        // Giả lập cập nhật dữ liệu và tìm kiếm lại
        updatePrices(prices, n);
        result = searchPrice(prices, n, target);
        
        if (result != -1) {
            cout << "Giá " << target << " tìm thấy tại chỉ số: " << result << endl;
        } else {
            cout << "Giá " << target << " vẫn không tìm thấy sau khi cập nhật." << endl;
        }
    }
    return 0;
}
