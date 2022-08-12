  // Deque implementation.

#include <iostream>
#include <string>

class Deque_Array {
 private:
    int head;
    int tail;
    int size;
    int capacity;
    int* array;

 public:
    Deque_Array() {
        head = -1;
        tail = -1;
        size = 0;
        capacity = 100;
        array = new int[capacity];
    }

    void push_front(int item) {
        if (head == -1) {
            head = 0;
            tail = 0;
        } else {
            head = (head + capacity - 1) % capacity;
        }
        array[head] = item;
        ++size;
    }

    void push_back(int item) {
        if (head == -1) {
            head = 0;
            tail = 0;
        } else {
            tail = (tail + 1) % capacity;
        }
        array[tail] = item;
        ++size;
    }

    int pop_front() {
        if (isEmpty()) {
            throw "error\n";
        }

        int popped = array[head];
        head = (head + 1) % capacity;
        --size;

        return popped;
    }

    int pop_back() {
        if (isEmpty()) {
            throw "error\n";
        }

        int popped = array[tail];
        tail = (tail + capacity - 1) % capacity;
        --size;

        return popped;
    }

    int front() {
        if (isEmpty()) {
            throw "error\n";
        }

        return array[head];
    }

    int back() {
        if (isEmpty()) {
            throw "error\n";
        }

        return array[tail];
    }

    int get_size() {
        return size;
    }

    void clear() {
        delete[] array;
        head = -1;
        tail = -1;
        size = 0;
        array = new int[capacity];
    }

    void exit() {
        std::cout << "bye\n";
    }

    bool isEmpty() {
        return(size == 0);
    }

    ~Deque_Array() {
        delete[] array;
        array = nullptr;
    }
};

int main() {
    Deque_Array array;
    std::string command;
    int number;
    while (std::cin >> command) {
        if (command != "exit") {
            if (command == "push_front") {
                std::cin >> number;
                array.push_front(number);
                std::cout << "ok\n";
            } else if (command == "push_back") {
                std::cin >> number;
                array.push_back(number);
                std::cout << "ok\n";
            } else if (command == "pop_front") {
                try {
                    std::cout << array.pop_front() << "\n";
                }
                catch (const char* message) {
                    std::cout << message;
                }
            } else if (command == "pop_back") {
                try {
                    std::cout << array.pop_back() << "\n";
                }
                catch (const char* message) {
                    std::cout << message;
                }
            } else if (command == "front") {
                try {
                    std::cout << array.front() << "\n";
                }
                catch (const char* message) {
                    std::cout << message;
                }
            } else if (command == "back") {
                try {
                    std::cout << array.back() << "\n";
                }
                catch (const char* message) {
                    std::cout << message;
                }
            } else if (command == "size") {
                std::cout << array.get_size() << "\n";
            } else if (command == "clear") {
                array.clear();
                std::cout << "ok\n";
            }
        } else {
            array.exit();
            break;
        }
    }

    return 0;
}
