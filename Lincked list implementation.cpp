// Linked list with insert and remove.

#include <iostream>
#include <string>

struct Node {
    Node* next;
    int data;

    explicit Node(int data) {
        this->data = data;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head_;
    Node* tail_;
    int size_;

public:
    LinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    bool isEmpty() {
        return head_ == nullptr;
    }

    void push(int data) {
        Node* new_item = new Node(data);
        if (isEmpty()) {
            head_ = new_item;
            tail_ = new_item;
        } else {
            tail_->next = new_item;
            tail_ = new_item;
        }
        ++size_;
    }

    void insert(int data, int position) {
        Node* new_item = new Node(data);
        if (position == size_ - 1) {
            tail_->next = new_item;
            tail_ = tail_->next;
        } else {
            Node* current = head_;
            for (int index = 0; index < position; ++index) {
                current = current->next;
            }
            new_item->next = current->next;
            current->next = new_item;
        }
        ++size_;
    }

    void remove(int position) {
        Node* current = head_;
        for (int index = 0; index < position; ++index) {
            current = current->next;
        }

        Node* delete_item = current->next;
        current->next = current->next->next;
        delete_item->next = nullptr;
        delete delete_item;
        --size_;
    }

    void print() {
        Node* current = head_;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }

    ~LinkedList() {
        Node* current = head_;
        while (current) {
            Node* delete_item = current;
            current = current->next;
            delete delete_item;
        }
    }
};

int main() {
    int length, amount_of_commands;
    std::cin >> length >> amount_of_commands;

    LinkedList list;
    for (int index = 0; index < length; ++index) {
        int data;
        std::cin >> data;
        list.push(data);
    }

    for (int index = 0; index < amount_of_commands; ++index) {
        std::string command;
        std::cin >> command;
        int data, position;
        if (command == "insert") {
            std::cin >> data >> position;
            list.insert(data, position);
        } else if (command == "remove") {
            std::cin >> position;
            list.remove(position);
        }
    }

    list.print();

    return 0;
}
