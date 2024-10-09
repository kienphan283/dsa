#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> tokens;

public:
    AuthenticationManager(int ttl) : timeToLive(ttl) {}

    void generate(const string& tokenId, int currentTime) {
        tokens[tokenId] = currentTime + timeToLive;
    }

    void renew(const string& tokenId, int currentTime) {
        if (tokens.count(tokenId) && tokens[tokenId] > currentTime) {
            tokens[tokenId] = currentTime + timeToLive;
        }
    }

    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        for (const auto& token : tokens) {
            if (token.second > currentTime) count++;
        }
        return count;
    }
};

void processAuthenticationManager() {
    vector<string> commands = {
        "AuthenticationManager", "renew", "generate", "countUnexpiredTokens",
        "generate", "renew", "renew", "countUnexpiredTokens"
    };
    
    vector<vector<string>> args = {
        {"5"}, {"aaa", "1"}, {"aaa", "2"}, {"6"}, 
        {"bbb", "7"}, {"aaa", "8"}, {"bbb", "10"}, {"15"}
    };

    AuthenticationManager* authManager = nullptr;
    vector<string> results;

    for (size_t i = 0; i < commands.size(); ++i) {
        const string& command = commands[i];

        if (command == "AuthenticationManager") {
            authManager = new AuthenticationManager(stoi(args[i][0]));
            results.push_back("null");
        } else if (command == "generate") {
            authManager->generate(args[i][0], stoi(args[i][1]));
            results.push_back("null");
        } else if (command == "renew") {
            authManager->renew(args[i][0], stoi(args[i][1]));
            results.push_back("null");
        } else if (command == "countUnexpiredTokens") {
            results.push_back(to_string(authManager->countUnexpiredTokens(stoi(args[i][0]))));
        }
    }

    cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << results[i] << (i < results.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;

    delete authManager;
}

int main() {
    processAuthenticationManager();
    return 0;
}
