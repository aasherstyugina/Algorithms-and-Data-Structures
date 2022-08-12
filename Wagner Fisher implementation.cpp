#include <iostream>
#include <algorithm>
#include <string>

int algorithmVF(const std::string& first, const std::string& second) {
    int first_size = first.size();
    int second_size = second.size();
    if (first_size == 0) {
        return second_size;
    }
    if (second_size == 0) {
        return first_size;
    }

    int** table = new int*[first_size + 1];
    for (int i = 0; i <= first_size; ++i) {
        table[i] = new int[second_size + 1];
    }

    for (int i = 0; i <= first_size; ++i) {
        table[i][0] = i;
    }
    for (int j = 0; j <= second_size; ++j) {
        table[0][j] = j;
    }
    for (int j = 1; j <= second_size; ++j) {
        for (int i = 1; i <= first_size; ++i) {
            if (first[i - 1] == second[j - 1]) {
                table[i][j] = table[i - 1][j - 1];
            } else {
                table[i][j] =
                    std::min(std::min(table[i][j - 1], table[i - 1][j]), table[i - 1][j - 1]) + 1;
            }
        }
    }

    int result = table[first_size][second_size];

    for (int i = 0; i <= first_size; ++i) {
        delete[] table[i];
        table[i] = nullptr;
    }
    delete[] table;
    table = nullptr;

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string first, second;
    std::getline(std::cin, first);
    std::getline(std::cin, second);

    std::cout << algorithmVF(first, second);

    return 0;
}
