#include <iostream>
#include <utility>
#include <string>
#include <map>

struct Node {
public:
    Node(char value, std::string code) {
        value_ = value;
        left_ = nullptr;
        right_ = nullptr;
        code_ = code;
    }

    void setChild(Node* node, bool is_left) {
        if (is_left) {
            left_ = node;
        } else {
            right_ = node;
        }
    }

    Node* getLeft() {
        return left_;
    }

    Node* getRight() {
        return right_;
    }

    void setValue(char value) {
        value_ = value;
    }
    char getValue() {
        return value_;
    }

    ~Node() {
        if (left_) {
            delete left_;
        }
        if (right_) {
            delete right_;
        }
    }

private:
    Node* left_;
    Node* right_;
    std::string code_;
    char value_;
};

Node* makeNodeTree(const std::map<char, std::string>& code_table) {
    Node* root = new Node('-', "");
    for (std::pair<char, std::string> elem : code_table) {
        Node* current = root;
        std::string current_code;
        for (char ch : elem.second) {
            current_code += ch;
            if (ch == '0') {
                Node* left = current->getLeft();
                if (!left) {
                    current->setChild(new Node('-', current_code), true);
                }
                current = current->getLeft();
            } else {
                Node* right = current->getRight();
                if (!right) {
                    current->setChild(new Node('-', current_code), false);
                }
                current = current->getRight();
            }
        }
        current->setValue(elem.first);
    }

    return root;
}

std::map<char, std::string> readTable(int size) {
    std::map<char, std::string> table;
    for (int i = 0; i < size; ++i) {
        std::string ch, code;
        std::cin >> ch >> code;
        table.emplace(ch[0], code);
    }

    return table;
}

std::string decode() {
    int size, length;
    std::cin >> size >> length;
    Node* root = makeNodeTree(readTable(size));
    std::string line;
    std::cin >> line;

    Node* current = root;
    std::string result;
    for (char ch : line) {
        if (ch == '0') {
            Node* left = current->getLeft();
            if (left) {
                current = left;
            } else {
                result += current->getValue();
                current = ch == '0' ? root->getLeft() : root->getRight();
            }
        } else {
            Node* right = current->getRight();
            if (right) {
                current = right;
            } else {
                result += current->getValue();
                current = ch == '0' ? root->getLeft() : root->getRight();
            }
        }
    }
    result += current->getValue();
    delete root;

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::cout << decode();

    return 0;
}
