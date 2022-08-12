#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int getIndexError(std::string num) {
    int result = 0;
    int current = 1;
    for (char ch : num) {
        if (ch == '1') {
            result += current;
        }
        current *= 2;
    }

    return result - 1;
}

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

std::string decodeHemmingCode(const std::string& input) {
    int columns = input.size();
    int rows = std::ceil(std::log2(columns));
    char** transform_matrix = getTransformMatrix(rows, columns);

    std::string error;
    for (int i = 0; i < rows; ++i) {
        int counter = 0;
        for (int j = 0; j < columns; ++j) {
            if (input[j] == '1' && transform_matrix[i][j] == '1') {
                ++counter;
            }
        }
        error += std::to_string(counter % 2)[0];
    }

    int error_index = getIndexError(error);
    int current = 1;
    int ind = 0;
    std::string result;
    while (ind < columns) {
        if (ind == current - 1) {
            current *= 2;
        } else {
            if (ind == error_index) {
                if (input[error_index] == '0') {
                    result += '1';
                } else {
                    result += '0';
                }
            } else {
                result += input[ind];
            }
        }
        ++ind;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] transform_matrix[i];
    }
    delete[] transform_matrix;

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string input;
    std::cin >> input;
    std::cout << decodeHemmingCode(input);

    return 0;
}
