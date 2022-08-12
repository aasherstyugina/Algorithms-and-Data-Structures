#include <iostream>

class Node {
public:
    int data_;
    int size_;
    Node* head_;
    Node* tail_;
    Node* next_;

    explicit Node(int data) {
        this->data_ = data;
        head_ = this;
        tail_ = this;
        next_ = nullptr;
        size_ = 1;
    }

    ~Node() {
        head_ = nullptr;
        tail_ = nullptr;
        next_ = nullptr;
    }
};

class DSU {
public:
    explicit DSU(int length) {
        length_ = length;
        items_ = new Node*[length];
        for (int index = 0; index < length; ++index) {
            items_[index] = new Node(index);
        }
    }

    void unite(int first, int second) {
        first = find(first);
        second = find(second);

        if (first == second) {
            return;
        }

        if (items_[first]->size_ > items_[second]->size_) {
            merge(items_[first], items_[second]);
        } else {
            merge(items_[second], items_[first]);
        }
    }

    void print() {
        if (length_ > 0) {
            Node* current = items_[0]->head_;
            while (current) {
                std::cout << current->data_ + 1 << " ";
                current = current->next_;
            }
        }
    }

    ~DSU() {
        if (length_ > 0) {
            Node* current = items_[0]->head_;
            while (current) {
                Node* del = current;
                current = current->next_;
                delete del;
            }
        }

        delete[] items_;
    }

private:
    int length_;
    Node** items_;

    int find(int number) {
        return items_[number - 1]->head_->data_;
    }

    void merge(Node* first, Node* second) {
        first->size_ += second->size_;
        first->tail_->next_ = second;
        first->tail_ = second->tail_;
        while (second) {
            second->head_ = first;
            second = second->next_;
        }
    }
};

int main() {
    int cats;
    std::cin >> cats;
    DSU* dsu = new DSU(cats);

    for (int index = 0; index < cats - 1; ++index) {
        int first_num, second_num;
        std::cin >> first_num >> second_num;
        dsu->unite(first_num, second_num);
    }

    dsu->print();

    delete dsu;
    dsu = nullptr;
}
