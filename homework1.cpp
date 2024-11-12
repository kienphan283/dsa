#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    string category;
    double price;
    string description;
};

void searchProducts(Product products[], int n, string query) {
    for (int i = 0; i < n; i++) {
        if (products[i].name.find(query) != string::npos || products[i].description.find(query) != string::npos) {
            cout << "Sản phẩm: " << products[i].name << ", Giá: " << products[i].price 
                 << ", Mô tả: " << products[i].description << endl;
        }
    }
}

int main() {
    Product products[] = {
        {"iPhone", "Điện thoại", 999.99, "Điện thoại Apple iPhone"},
        {"MacBook", "Laptop", 1999.99, "Laptop Apple MacBook"},
        {"AirPods", "Phụ kiện", 199.99, "Tai nghe Apple AirPods"}
    };
    int n = sizeof(products) / sizeof(products[0]);
    string query = "Apple";
    searchProducts(products, n, query);
    return 0;
}
