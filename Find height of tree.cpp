// Find height of binary search tree.

#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    explicit Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

class Tree {
public:
    explicit Tree(int value) {
        root_ = new Node(value);
    }

    void insert(Node* node, int value) {
        if (value < node->value) {
            if (node->left) {
                insert(node->left, value);
            } else {
                node->left = new Node(value);
            }
        } else if (value > node->value) {
            if (node->right) {
                insert(node->right, value);
            } else {
                node->right = new Node(value);
            }
        }
    }

    int getHeight(Node* current) {
        if (!current) {
            return 0;
        }

        int left_height = getHeight(current->left) + 1;
        int right_height = getHeight(current->right) + 1;

        return left_height > right_height ? left_height : right_height;
    }

    Node* getRoot() {
        return root_;
    }

    ~Tree() {
        deleteNode(root_);
    }

private:
    Node* root_;

    void deleteNode(Node* current) {
        if (current) {
            deleteNode(current->left);
            deleteNode(current->right);
            delete current;
            current = nullptr;
        }
    }
};

int main() {
    int number;
    std::cin >> number;

    if (number != 0) {
        Tree* tree = new Tree(number);

        while (true) {
            std::cin >> number;
            if (number == 0) {
                std::cout << tree->getHeight(tree->getRoot());
                break;
            }
            tree->insert(tree->getRoot(), number);
        }

        delete tree;
        tree = nullptr;
    } else {
        std::cout << 0;
    }

    return 0;
}
