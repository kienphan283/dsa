#include <iostream>
#include <vector>
using namespace std;

class BrowserHistory {
private:
    vector<string> history;
    int currentIndex = 0;

public:
    BrowserHistory(const string& homepage) {
        history.push_back(homepage);
    }

    void visit(const string& url) {
        history.erase(history.begin() + currentIndex + 1, history.end());
        history.push_back(url);
        currentIndex++;
    }

    string back(int steps) {
        currentIndex = max(0, currentIndex - steps);
        return history[currentIndex];
    }

    string forward(int steps) {
        currentIndex = min((int)history.size() - 1, currentIndex + steps);
        return history[currentIndex];
    }
};

void processBrowserHistory() {
    vector<string> commands = {"BrowserHistory", "visit", "visit", "visit", "back", "back", "forward", "visit", "forward", "back", "back"};
    vector<vector<string>> args = {{"uit.edu.vn"}, {"google.com"}, {"facebook.com"}, {"youtube.com"}, {"1"}, {"1"}, {"1"}, {"linkedin.com"}, {"2"}, {"2"}, {"7"}};

    BrowserHistory* browserHistory = nullptr;
    vector<string> results;

    for (size_t i = 0; i < commands.size(); ++i) {
        const string& command = commands[i];

        if (command == "BrowserHistory") {
            browserHistory = new BrowserHistory(args[i][0]);
            results.push_back("null");
        } else if (command == "visit") {
            browserHistory->visit(args[i][0]);
            results.push_back("null");
        } else if (command == "back") {
            results.push_back(browserHistory->back(stoi(args[i][0])));
        } else if (command == "forward") {
            results.push_back(browserHistory->forward(stoi(args[i][0])));
        }
    }

    cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << "\"" << results[i] << "\"" << (i < results.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;

    delete browserHistory;
}

int main() {
    processBrowserHistory();
    return 0;
}
