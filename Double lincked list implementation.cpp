// Doble linked list implementation.

#include <iostream>
#include <string>

struct Node {
    Node* previous;
    Node* next;
    int data;

    explicit Node(int data) {
        this->data = data;
        next = nullptr;
        previous = nullptr;
    }
};

class DoubleLinkedList {
private:
    Node* head_;
    Node* tail_;
    int size_;

public:
    DoubleLinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    bool isEmpty() {
        return head_ == nullptr;
    }

    void pushFront(int data) {
        Node* new_item = new Node(data);
        if (isEmpty()) {
            head_ = new_item;
            tail_ = new_item;
        } else {
            new_item->next = head_;
            head_->previous = new_item;
            head_ = new_item;
        }
        ++size_;
    }

    void pushBack(int data) {
        Node* new_item = new Node(data);
        if (isEmpty()) {
            head_ = new_item;
            tail_ = new_item;
        } else {
            new_item->previous = tail_;
            tail_->next = new_item;
            tail_ = new_item;
        }
        ++size_;
    }

    void insert(int data, int position) {
        Node* new_item = new Node(data);
        Node* current = head_;
        for (int index = 0; index < position; ++index) {
            current = current->next;
        }
        new_item->next = current->next;
        new_item->previous = current;
        current->next = new_item;
        new_item->next->previous = new_item;
        ++size_;
    }

    void remove(int position) {
        if (position == size_ - 2) {
            tail_ = tail_->previous;
            tail_->next->previous = nullptr;
            delete tail_->next;
            tail_->next = nullptr;
        } else {
            Node* current = head_;
            for (int index = 0; index < position + 1; ++index) {
                current = current->next;
            }

            current->previous->next = current->next;
            current->next->previous = current->previous;
            current->next = nullptr;
            current->previous = nullptr;
            delete current;
        }
        --size_;
    }

    void print() {
        Node* current = head_;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }

    void printReverse() {
        Node* current = tail_;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->previous;
        }
    }

    ~DoubleLinkedList() {
        Node* current = head_;
        while (current != nullptr) {
            if (current->next != nullptr) {
                current = current->next;
                current->previous->next = nullptr;
                delete current->previous;
                current->previous = nullptr;
            } else {
                delete current;
                current = nullptr;
            }
        }
    }
};

int main() {
    int length, amount_of_commands;
    std::cin >> length >> amount_of_commands;

    DoubleLinkedList list;
    for (int index = 0; index < length; ++index) {
        int data;
        std::cin >> data;
        list.pushBack(data);
    }

    for (int index = 0; index < amount_of_commands; ++index) {
        std::string command;
        std::cin >> command;
        int data, position;
        if (command == "push_front") {
            std::cin >> data;
            list.pushFront(data);
        } else if (command == "push_back") {
            std::cin >> data;
            list.pushBack(data);
        } else if (command == "insert") {
            std::cin >> data >> position;
            list.insert(data, position);
        } else if (command == "remove") {
            std::cin >> position;
            list.remove(position);
        }
    }

    list.print();
    std::cout << "\n";
    list.printReverse();

    return 0;
}
