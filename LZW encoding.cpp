#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <vector>

std::map<std::string, int> initializeDictionary() {
    std::map<std::string, int> dictionary;
    for (int i = 0; i < 128; ++i) {
        char ch = i;
        std::string symbol(1, i);
        dictionary.emplace(symbol, i);
    }

    return dictionary;
}

std::vector<int> algorithmLZW(const std::string& input) {
    std::string current;
    std::vector<int> result;
    std::map<std::string, int> dictionary = initializeDictionary();
    for (char ch : input) {
        if (dictionary.count(current + ch) != 0) {
            current += ch;
        } else {
            result.push_back(dictionary.find(current)->second);
            dictionary.emplace(current + ch, dictionary.size());
            current = ch;
        }
    }
    result.push_back(dictionary.find(current)->second);

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string input;
    getline(std::cin, input);
    std::vector<int> result = algorithmLZW(input);
    std::cout << result.size() << "\n";
    for (int num : result) {
        std::cout << num << " ";
    }

    return 0;
}
