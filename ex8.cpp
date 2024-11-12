#include <iostream>
using namespace std;

struct Point {
    int x, y;
};

struct KDNode {
    Point point;
    KDNode *left, *right;
};

KDNode* createNode(int x, int y) {
    KDNode* node = new KDNode();
    node->point.x = x;
    node->point.y = y;
    node->left = node->right = NULL;
    return node;
}

int main() {
    KDNode* root = createNode(3, 6);
    root->left = createNode(2, 7);
    root->right = createNode(17, 15);
    cout << "KD Tree đã được tạo với các điểm cơ bản." << endl;
    return 0;
}
