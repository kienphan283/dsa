#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return top->data;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

bool isValidBrackets(const string& s) {
    Stack stack;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.isEmpty()) return false;
            char top = stack.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}

string reverseWords(const string& str) {
    Stack stack;
    string result;
    for (char c : str) {
        if (c != ' ') {
            stack.push(c);
        } else {
            while (!stack.isEmpty()) {
                result += static_cast<char>(stack.pop());
            }
            result += ' ';
        }
    }
    // Pop the last word from the stack
    while (!stack.isEmpty()) {
        result += static_cast<char>(stack.pop());
    }
    return result;
}

int main() {
    int choice;
    string input;
    Stack stack;

    do {
        cout << "\nMenu:\n";
        cout << "1. Thêm phần tử vào stack\n";
        cout << "2. Kiểm tra stack có rỗng không\n";
        cout << "3. Lấy phần tử trên cùng của stack\n";
        cout << "4. Kiểm tra chuỗi ngoặc hợp lệ\n";
        cout << "5. Đảo ngược từng từ trong chuỗi\n";
        cout << "6. Thoát\n";
        cout << "Nhập lựa chọn của bạn: ";
        
        if (!(cin >> choice)) {
            cout << "Lựa chọn không hợp lệ. Vui lòng nhập một số.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                int value;
                cout << "Nhập giá trị để thêm vào stack: ";
                if (cin >> value) {
                    stack.push(value);
                    cout << "Đã thêm " << value << " vào stack.\n";
                } else {
                    cout << "Giá trị không hợp lệ. Vui lòng nhập một số nguyên.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case 2:
                cout << (stack.isEmpty() ? "Stack rỗng" : "Stack không rỗng") << endl;
                break;
            case 3:
                if (!stack.isEmpty()) {
                    cout << "Phần tử trên cùng của stack: " << stack.peek() << endl;
                } else {
                    cout << "Stack rỗng, không có phần tử để lấy.\n";
                }
                break;
            case 4:
                cout << "Nhập chuỗi để kiểm tra ngoặc hợp lệ: ";
                getline(cin, input);
                cout << (isValidBrackets(input) ? "Hợp lệ" : "Không hợp lệ") << endl;
                break;
            case 5:
                cout << "Nhập chuỗi để đảo ngược từng từ: ";
                getline(cin, input);
                cout << "Chuỗi đã đảo ngược: " << reverseWords(input) << endl;
                break;
            case 6:
                cout << "Thoát chương trình...\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng chọn lại.\n";
        }
    } while (choice != 6);

    return 0;
}