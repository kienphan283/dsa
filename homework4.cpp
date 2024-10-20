#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minCoins(vector<int>& prices) {
    int n = prices.size();
    sort(prices.begin(), prices.end());  // Sort prices in ascending order
    int totalCoins = 0;

    for (int i = 0; i < n; i += 2) {
        totalCoins += prices[i];  // Buy fruit i, get fruit i+1 for free
    }

    return totalCoins;
}

int main() {
    int n;
    cout << "Enter the number of fruits: ";
    cin >> n;
    vector<int> prices(n);
    
    cout << "Enter the prices of fruits: ";
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    int result = minCoins(prices);

    cout << "Minimum coins required: " << result << " coins" << endl;
    
    return 0;
}
