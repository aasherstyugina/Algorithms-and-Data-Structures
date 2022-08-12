#include <iostream>

struct Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

class SplayTree {
public:
    SplayTree() {
        root_ = nullptr;
    }

    ~SplayTree() {
        deleteNode(root_);
    }

    void insert(int key) {
        if (find(key)) {
            return;
        }

        if (!root_) {
            root_ = new Node(key);
            return;
        }

        Node* current = root_;
        while (current) {
            if (key > current->key) {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = new Node(key);
                    current->right->parent = current;
                    break;
                }
            } else if (key < current->key) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new Node(key);
                    current->left->parent = current;
                    break;
                }
            }
        }
    }

    Node* find(int key) const {
        Node* current = root_;
        while (current) {
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                return current;
            }
        }

        return nullptr;
    }

    int splay(Node* child) {
        if (!child->parent) {
            return 0;
        }

        Node* parent = child->parent;
        Node* grandparent = parent->parent;
        if (!grandparent) {
            if (parent->key > child->key) {
                return zig(parent);
            } else {
                return zag(parent);
            }
        }

        if (grandparent->key > parent->key && parent->key > child->key) {
            return zigZig(child) + splay(child);
        } else if (grandparent->key < parent->key && parent->key < child->key) {
            return zagZag(child) + splay(child);
        } else if (grandparent->key > parent->key && parent->key < child->key) {
            return zagZig(child) + splay(child);
        } else if (grandparent->key < parent->key && parent->key > child->key) {
            return zigZag(child) + splay(child);
        }
    }

    int getHeight() const {
        if (!root_) {
            return 0;
        }

        return countHeight(root_) - 1;
    }

private:
    Node* root_;

    int zig(Node* pivot) {
        Node* node = pivot->left;
        pivot->left = node->right;

        if (node->right) {
            node->right->parent = pivot;
        }
        node->parent = pivot->parent;
        if (pivot->parent) {
            if (pivot == pivot->parent->left) {
                pivot->parent->left = node;
            } else {
                pivot->parent->right = node;
            }
        } else {
            root_ = node;
        }
        node->right = pivot;
        pivot->parent = node;

        return 1;
    }

    int zag(Node* pivot) {
        Node* node = pivot->right;
        pivot->right = node->left;

        if (node->left) {
            node->left->parent = pivot;
        }
        node->parent = pivot->parent;
        if (pivot->parent) {
            if (pivot == pivot->parent->left) {
                pivot->parent->left = node;
            } else {
                pivot->parent->right = node;
            }
        } else {
            root_ = node;
        }
        node->left = pivot;
        pivot->parent = node;

        return 1;
    }

    int zigZig(Node* pivot) {
        return zig(pivot->parent->parent) + zig(pivot->parent);
    }

    int zigZag(Node* pivot) {
        return zig(pivot->parent) + zag(pivot->parent) - 1;
    }

    int zagZig(Node* pivot) {
        return zag(pivot->parent) + zig(pivot->parent) - 1;
    }

    int zagZag(Node* pivot) {
        return zag(pivot->parent->parent) + zag(pivot->parent);
    }

    int countHeight(Node* current) const {
        if (!current) {
            return 0;
        }

        int left_height = countHeight(current->left) + 1;
        int right_height = countHeight(current->right) + 1;

        return left_height > right_height ? left_height : right_height;
    }

    void deleteNode(Node* current) {
        if (current) {
            deleteNode(current->left);
            deleteNode(current->right);
            current->parent = nullptr;
            delete current;
        }
    }
};
