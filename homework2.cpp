#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<string> backStack, forwardStack;
string currentURL = "homepage";

// Function to visit a new URL
void visit(const string& url) {
    if (currentURL != "") {
        backStack.push(currentURL);  // Push current URL to backStack
    }
    currentURL = url;  // Update current URL
    // Clear forwardStack after visiting a new URL
    while (!forwardStack.empty()) {
        forwardStack.pop();
    }
    cout << "Visiting: " << currentURL << endl;
}

// Function to go back to the previous URL
void goBack() {
    if (backStack.empty()) {
        cout << "Cannot go back\n";
        return;
    }
    forwardStack.push(currentURL);  // Push current URL to forwardStack
    currentURL = backStack.top();   // Get the previous URL from backStack
    backStack.pop();                // Remove the previous URL from backStack
    cout << "Going back to: " << currentURL << endl;
}

// Function to go forward to the next URL
void goForward() {
    if (forwardStack.empty()) {
        cout << "Cannot go forward\n";
        return;
    }
    backStack.push(currentURL);     // Push current URL to backStack
    currentURL = forwardStack.top(); // Get the next URL from forwardStack
    forwardStack.pop();              // Remove the next URL from forwardStack
    cout << "Going forward to: " << currentURL << endl;
}

int main() {
    int choice;
    string url;
    do {
        cout << "\n1. Visit a new URL\n2. Go back\n3. Go forward\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter URL to visit: ";
                cin >> url;
                visit(url);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
