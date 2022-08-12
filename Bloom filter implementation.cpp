#include <iostream>
#include <string>

// основной класс фильтра
class BloomFilter {
public:
    BloomFilter(size_t hashes, size_t bits) {
        hashes_ = hashes;
        bits_ = bits;
        tree_ = new Tree();
        filter_ = new bool[bits];
        for (size_t index = 0; index < bits; ++index) {
            filter_[index] = false;
        }
        total_request_ = 0;
        false_positive_request_ = 0;
    }

    ~BloomFilter() {
        delete tree_;
        delete[] filter_;
    }

    // вставка информации об объекте
    void add(const std::string& obj) {
        size_t* hash_codes = new size_t[hashes_];
        if (hashes_ > 0) {
            hash_codes[0] = std::hash<std::string>{}(obj) % bits_;
            filter_[hash_codes[0]] = true;
        }
        for (size_t index = 1; index < hashes_; ++index) {
            hash_codes[index] = std::hash<std::string>{}(obj + std::to_string(index)) % bits_;
            filter_[hash_codes[index]] = true;
        }

        tree_->insert(obj);

        delete[] hash_codes;
    }

    // проверка принадлежности объекта
    bool verify(const std::string& obj) {
        ++total_request_;
        bool test = true;
        size_t* hash_codes = new size_t[hashes_];
        if (hashes_ > 0) {
            hash_codes[0] = std::hash<std::string>{}(obj) % bits_;
            if (!filter_[hash_codes[0]]) {
                test = false;
            }
        }
        for (size_t index = 1; index < hashes_; ++index) {
            hash_codes[index] = std::hash<std::string>{}(obj + std::to_string(index)) % bits_;
            if (!filter_[hash_codes[index]]) {
                test = false;
            }
        }
        delete[] hash_codes;

        if (test) {
            if (!tree_->find(obj)) {
                ++false_positive_request_;
            }
            return true;
        } else {
            return false;
        }
    }

    // считаем относительную величину false positive rate по запросам тестирования
    // принадлежности
    double getFPRate() const {
        return total_request_ == 0 ? 0 : (false_positive_request_ + 0.0) / total_request_;
    }

    size_t numberOfHashFunctions() const {
        return hashes_;
    }

    size_t numberOfBits() const {
        return bits_;
    }

private:
    struct Node {
        int count;
        Node** next;

        Node() {
            count = 0;
            next = new Node*[256];
            for (int index = 0; index < 256; ++index) {
                next[index] = nullptr;
            }
        }

        ~Node() {
            for (int index = 0; index < 256; ++index) {
                if (next[index]) {
                    delete next[index];
                }
            }

            delete[] next;
        }
    };

    class Tree {
    public:
        Tree() {
            root_ = new Node();
        }

        void insert(std::string str) {
            Node* current = root_;
            for (size_t index = 0; index < str.length(); ++index) {
                size_t symbol = static_cast<size_t>(str[index]);
                if (!current->next[symbol]) {
                    current->next[symbol] = new Node();
                }
                current = current->next[symbol];
            }

            ++current->count;
        }

        bool find(std::string str) {
            Node* current = root_;
            for (size_t index = 0; index < str.length(); ++index) {
                size_t symbol = static_cast<size_t>(str[index]);
                current = current->next[symbol];
                if (!current) {
                    return false;
                }
            }

            return current->count > 0;
        }

        ~Tree() {
            delete root_;
        }

    private:
        Node* root_;
    };

    size_t hashes_;
    size_t bits_;
    bool* filter_;
    Tree* tree_;
    size_t total_request_;
    size_t false_positive_request_;
};
