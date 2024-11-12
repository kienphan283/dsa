#include <iostream>
#include <string>
using namespace std;

struct Node {
    string url;
    int timestamp;
    Node *left, *right;
};

Node* createNode(string url, int timestamp) {
    Node* node = new Node();
    node->url = url;
    node->timestamp = timestamp;
    node->left = node->right = nullptr;
    return node;
}

Node* insertNode(Node* root, string url, int timestamp) {
    if (root == nullptr) return createNode(url, timestamp);
    if (url < root->url) root->left = insertNode(root->left, url, timestamp);
    else if (url > root->url) root->right = insertNode(root->right, url, timestamp);
    return root;
}

Node* searchURL(Node* root, string url) {
    if (root == nullptr || root->url == url) return root;
    if (url < root->url) return searchURL(root->left, url);
    return searchURL(root->right, url);
}

int main() {
    Node* root = nullptr;
    root = insertNode(root, "google.com", 1);
    root = insertNode(root, "facebook.com", 2);
    root = insertNode(root, "youtube.com", 3);

    string searchUrl = "facebook.com";
    Node* result = searchURL(root, searchUrl);
    if (result)
        cout << "Trang web " << result->url << " tìm thấy với timestamp: " << result->timestamp << endl;
    else
        cout << "Trang web không tìm thấy." << endl;
    return 0;
}
