#include <iostream>
#include <string>
#include <vector>

std::string getBinary(int num, int length) {
    std::string result;
    while (num > 0) {
        result += std::to_string(num % 2);
        num /= 2;
    }
    while (result.size() < length) {
        result += "0";
    }

    return result;
}

char** getTransformMatrix(int rows, int columns) {
    char** matrix = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new char[columns];
    }
    for (int j = 0; j < columns; ++j) {
        std::string binary = getBinary(j + 1, rows);
        for (int i = 0; i < rows; ++i) {
            matrix[i][j] = binary[i];
        }
    }

    return matrix;
}

std::vector<char> getHemmingCode(const std::string& input) {
    int current_control = 1;
    std::vector<int> controls;
    int size = input.size();
    std::vector<char> hemming;

    int ind = 0;
    while (ind < input.size()) {
        if (hemming.size() + 1 == current_control) {
            hemming.push_back('0');
            controls.push_back(current_control - 1);
            current_control *= 2;
        } else {
            hemming.push_back(input[ind]);
            ++ind;
        }
    }

    int controls_size = controls.size();
    int hemming_size = hemming.size();
    char** transform_matrix = getTransformMatrix(controls_size, hemming_size);

    for (int i = 0; i < controls_size; ++i) {
        int counter = 0;
        for (int j = 0; j < hemming_size; ++j) {
            if (hemming[j] == '1' && transform_matrix[i][j] == '1') {
                ++counter;
            }
        }
        hemming[controls[i]] = std::to_string(counter % 2)[0];
    }

    for (int i = 0; i < controls_size; ++i) {
        delete[] transform_matrix[i];
    }
    delete[] transform_matrix;

    return hemming;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string input;
    std::cin >> input;
    for (char ch : getHemmingCode(input)) {
        std::cout << ch;
    }

    return 0;
}
