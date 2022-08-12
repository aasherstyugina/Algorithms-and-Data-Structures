#include <iostream>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node* next_;

    Node(KeyType key, ValueType value) {
        key_ = key;
        value_ = value;
        next_ = nullptr;
    }
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable() {
        capacity_ = 100;
        size_ = 0;
        fullness_ = 0.5;
        hasher_ = Func();
        table_ = new Node<KeyType, ValueType>*[capacity_];
        for (size_t index = 0; index < capacity_; ++index) {
            table_[index] = nullptr;
        }
    }

    explicit HashTable(Func func) {
        capacity_ = 100;
        size_ = 0;
        fullness_ = 0.5;
        hasher_ = Func(func);
        table_ = new Node<KeyType, ValueType>*[capacity_];
        for (size_t index = 0; index < capacity_; ++index) {
            table_[index] = nullptr;
        }
    }
    HashTable(size_t capacity, double fullness, Func func = std::hash<KeyType>()) {
        capacity_ = capacity;
        size_ = 0;
        fullness_ = fullness > 0 && fullness <= 1 ? fullness : 0.5;
        hasher_ = Func(func);
        table_ = new Node<KeyType, ValueType>*[capacity_];
        for (size_t index = 0; index < capacity_; ++index) {
            table_[index] = nullptr;
        }
    }

    ~HashTable() {
        for (size_t index = 0; index < capacity_; ++index) {
            if (table_[index]) {
                Node<KeyType, ValueType>* del = table_[index]->next_;
                while (del) {
                    table_[index]->next_ = del->next_;
                    delete del;
                    del = table_[index]->next_;
                }
                delete table_[index];
            }
        }
        delete[] table_;
    }

    void insert(KeyType key, ValueType value) {
        if (capacity_ == 0) {
            return;
        }

        ValueType* value_node = find(key);
        if (value_node) {
            *value_node = value;
        } else {
            size_t hash_code = hasher_(key) % capacity_;
            if (table_[hash_code]) {
                Node<KeyType, ValueType>* current = table_[hash_code];
                while (current->next_) {
                    current = current->next_;
                }
                current->next_ = new Node<KeyType, ValueType>(key, value);
            } else {
                table_[hash_code] = new Node<KeyType, ValueType>(key, value);
            }

            ++size_;
        }

        if ((size_ + 0.0) / capacity_ > fullness_) {
            rehash();
        }
    }

    ValueType* find(KeyType key) {
        if (capacity_ == 0) {
            return nullptr;
        }

        size_t hash_code = hasher_(key) % capacity_;
        Node<KeyType, ValueType>* current = table_[hash_code];
        while (current) {
            if (current->key_ == key) {
                return &current->value_;
            } else {
                current = current->next_;
            }
        }
        return nullptr;
    }

    void erase(KeyType key) {
        if (!find(key)) {
            return;
        }

        size_t hash_code = hasher_(key) % capacity_;
        Node<KeyType, ValueType>* current = table_[hash_code];
        Node<KeyType, ValueType>* parent = nullptr;
        while (current && current->key_ != key) {
            parent = current;
            current = current->next_;
        }
        if (parent) {
            parent->next_ = current->next_;
        } else {
            table_[hash_code] = current->next_;
        }
        current->next_ = nullptr;
        delete current;

        --size_;
    }

    Node<KeyType, ValueType>& operator[](uint64_t hash_code) {
        if (hash_code >= capacity_) {
            throw std::out_of_range("");
        }

        if (!table_[hash_code]) {
            throw std::runtime_error("");
        }

        return *table_[hash_code];
    }

    Node<KeyType, ValueType> at(uint64_t hash_code) {
        if (hash_code >= capacity_) {
            throw std::out_of_range("");
        }

        if (!table_[hash_code]) {
            throw std::runtime_error("");
        }

        return *table_[hash_code];
    }

    size_t size() const {
        return size_;
    }
    size_t capacity() const {
        return capacity_;
    }

private:
    size_t capacity_;
    size_t size_;
    double fullness_;
    Func hasher_;
    Node<KeyType, ValueType>** table_;

    void rehash() {
        Node<KeyType, ValueType>** new_table = new Node<KeyType, ValueType>*[capacity_ * 2];
        for (size_t index = 0; index < capacity_ * 2; ++index) {
            new_table[index] = nullptr;
        }

        for (size_t index = 0; index < capacity_; ++index) {
            Node<KeyType, ValueType>* current = table_[index];
            while (current) {
                size_t hash_code = hasher_(current->key_) % (capacity_ * 2);
                if (new_table[hash_code]) {
                    Node<KeyType, ValueType>* node = new_table[hash_code];
                    while (node->next_) {
                        node = node->next_;
                    }
                    node->next_ = new Node<KeyType, ValueType>(current->key_, current->value_);
                } else {
                    new_table[hash_code] =
                        new Node<KeyType, ValueType>(current->key_, current->value_);
                }
                current = current->next_;
            }
        }

        for (size_t index = 0; index < capacity_; ++index) {
            if (table_[index]) {
                Node<KeyType, ValueType>* del = table_[index]->next_;
                while (del) {
                    table_[index]->next_ = del->next_;
                    delete del;
                    del = table_[index]->next_;
                }
                delete table_[index];
            }
        }
        delete[] table_;

        table_ = new_table;
        capacity_ *= 2;
    }
};
