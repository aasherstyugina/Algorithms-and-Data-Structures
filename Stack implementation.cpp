  // Stack implementation.

#include <iostream>
#include <string>

class Stack_Array {
 private:
    int top;
    int size;
    int capacity;
    int* array;

 public:
    Stack_Array() {
        top = -1;
        size = 0;
        capacity = 10;
        array = new int[capacity];
    }

    void push(int item) {
        if (size >= capacity) {
            capacity *= 2;
            int* new_array = new int[capacity];
            for (int index = 0; index < size; index++) {
                new_array[index] = array[index];
            }
            delete[] array;
            array = new_array;
        }

        array[size] = item;
        ++size;
        ++top;
    }

    int pop() {
        if (isEmpty()) {
            throw "error\n";
        }

        int popped = array[top];
        --top;
        --size;

        return popped;
    }

    int back() {
        if (isEmpty()) {
            throw "error\n";
        }

        return array[top];
    }

    int get_size() {
        return size;
    }

    void clear() {
        delete[] array;
        top = -1;
        size = 0;
        capacity = 10;
        array = new int[capacity];
    }

    void exit() {
        std::cout << "bye\n";
    }

    bool isEmpty() {
        return(top == -1);
    }

    ~Stack_Array() {
        delete[] array;
        array = nullptr;
    }
};

int main() {
    Stack_Array array;
    std::string command;
    while (std::cin >> command) {
        if (command != "exit") {
            if (command == "push") {
                int number;
                std::cin >> number;
                array.push(number);
                std::cout << "ok\n";
            } else if (command == "pop") {
                try {
                    std::cout << array.pop() << "\n";
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
