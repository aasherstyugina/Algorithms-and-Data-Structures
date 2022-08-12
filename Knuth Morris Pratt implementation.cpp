#include <iostream>
#include <vector>
#include <string>

std::vector<int> getBracesArray(const std::string& str) {
    int size = str.size();
    std::vector<int> result(size);
    int count = 0;

    for (int i = 1; i < size; ++i) {
        while (count > 0 && str[count] != str[i]) {
            count = result[count - 1];
        }
        if (str[count] == str[i]) {
            ++count;
        }

        result[i] = count;
    }

    return result;
}

std::vector<int> algorithmKMP(const std::string& substr, const std::string& str) {
    std::vector<int> result;
    int count = 0;
    int str_size = str.size();
    int substr_size = substr.size();

    std::vector<int> braces_array = getBracesArray(substr);
    for (int i = 0; i < str_size; ++i) {
        while (count > 0 && substr[count] != str[i]) {
            count = braces_array[count - 1];
        }
        if (substr[count] == str[i]) {
            ++count;
        }
        if (count == substr_size) {
            result.push_back(i - substr_size + 1);
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string substr, str;
    std::getline(std::cin, substr);
    std::getline(std::cin, str);

    if (substr.size() * str.size() == 0) {
        std::cout << 0 << "\n";
    } else {
        std::vector<int> result = algorithmKMP(substr, str);
        std::cout << result.size() << "\n";
        for (int pos : result) {
            std::cout << pos << "\n";
        }
    }

    return 0;
}
