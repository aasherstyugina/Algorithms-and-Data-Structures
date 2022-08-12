#include <iostream>
#include <utility>
#include <string>
#include <map>

struct Node {
public:
    Node(int frequency, std::string value) {
        frequency_ = frequency;
        value_ = value;
        left_ = nullptr;
        right_ = nullptr;
        code_ = "";
    }

    void setChildren(Node* left, Node* right) {
        left_ = left;
        right_ = right;
    }

    void addCode(std::string add) {
        code_ = add + code_;
        if (left_) {
            left_->addCode(add);
        }
        if (right_) {
            right_->addCode(add);
        }
    }

    Node* getLeft() {
        return left_;
    }

    Node* getRight() {
        return right_;
    }

    std::string getCode() {
        return code_;
    }

    std::string getValue() {
        return value_;
    }

    void fillCodeTable(std::map<char, std::string>* code_table) {
        if (value_.size() == 1) {
            code_table->emplace(value_[0], code_);
        }

        if (left_) {
            left_->fillCodeTable(code_table);
        }
        if (right_) {
            right_->fillCodeTable(code_table);
        }
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
    std::string value_;
    int frequency_;
};

std::multimap<int, std::string> getFreqTable(const std::string& input) {
    std::map<std::string, int> table;
    for (char ch : input) {
        std::string current(1, ch);
        if (table.count(current) == 0) {
            table.emplace(current, 1);
        } else {
            ++table[current];
        }
    }

    std::multimap<int, std::string> result;
    std::multimap<std::string, int>::iterator iter = table.begin();
    while (iter != table.end()) {
        result.emplace(iter->second, iter->first);
        ++iter;
    }

    table.clear();
    return result;
}

std::map<char, std::string> getCodeTable(const std::string& input) {
    std::multimap<int, std::string> freq_table = getFreqTable(input);
    std::map<char, std::string> code_table;

    if (freq_table.size() == 1) {
        code_table.emplace(freq_table.begin()->second[0], "0");
        return code_table;
    }

    std::map<std::string, Node*> existed_nodes;
    while (freq_table.size() > 1) {
        std::map<int, std::string>::iterator element = freq_table.begin();
        int freq_first = element->first;
        std::string value_first = element->second;
        Node* node_first;
        if (existed_nodes.count(value_first)) {
            node_first = existed_nodes.find(value_first)->second;
        } else {
            node_first = new Node(freq_first, value_first);
            existed_nodes.emplace(value_first, node_first);
        }
        node_first->addCode("0");

        ++element;
        std::string value_second = element->second;
        int freq_second = element->first;
        Node* node_second;
        if (existed_nodes.count(value_second)) {
            node_second = existed_nodes.find(value_second)->second;
        } else {
            node_second = new Node(freq_second, value_second);
            existed_nodes.emplace(value_second, node_second);
        }
        node_second->addCode("1");

        std::string value_parent = value_first + value_second;
        int freq_parent = freq_first + freq_second;
        Node* node_parent = new Node(freq_parent, value_parent);
        node_parent->setChildren(node_first, node_second);
        existed_nodes.emplace(value_parent, node_parent);

        freq_table.erase(freq_table.begin());
        freq_table.erase(freq_table.begin());
        freq_table.emplace(freq_parent, value_parent);
    }

    Node* root = existed_nodes.find(freq_table.begin()->second)->second;
    root->fillCodeTable(&code_table);
    delete root;

    return code_table;
}

std::string codeString(const std::string& input, const std::map<char, std::string>& table) {
    std::string result;
    for (char ch : input) {
        result += table.find(ch)->second;
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string input;
    std::cin >> input;
    std::map<char, std::string> code_table = getCodeTable(input);
    std::string result = codeString(input, code_table);

    std::cout << code_table.size() << " " << result.length() << "\n";
    for (std::pair<char, std::string> elem : code_table) {
        std::cout << elem.first << ": " << elem.second << "\n";
    }
    std::cout << result;

    return 0;
}
