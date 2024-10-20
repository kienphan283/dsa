#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> canSee(const vector<int>& heights) {
    int n = heights.size();
    vector<int> answer(n, 0);  // Kết quả sẽ lưu số lượng người mà mỗi người có thể nhìn thấy

    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = i + 1; j < n; ++j) {
            if (heights[j] > heights[i]) {  // Nếu người này cao hơn, kết thúc đếm
                count++;
                break;
            } else {  // Nếu người này thấp hơn, tiếp tục đếm
                count++;
            }
        }
        answer[i] = count;  // Ghi nhận số người có thể nhìn thấy cho người i
    }

    return answer;
}

int main() {
    int n;
    cout << "Enter number of people: ";
    cin >> n;

    vector<int> heights(n);
    cout << "Enter heights of people: ";
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    vector<int> result = canSee(heights);

    cout << "Result: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
