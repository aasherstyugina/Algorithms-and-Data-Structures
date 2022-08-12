#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <vector>

std::map<int, std::string> initializeDictionary() {
    std::map<int, std::string> dictionary;
    for (int i = 0; i < 128; ++i) {
        char ch = i;
        std::string symbol(1, i);
        dictionary.emplace(i, symbol);
    }

    return dictionary;
}

void algorithmLZWDecode() {
    int count;
    std::cin >> count;
    std::map<int, std::string> dictionary = initializeDictionary();

    int previous;
    std::cin >> previous;
    std::cout << dictionary[previous];
    char ch = previous;
    for (int ind = 1; ind < count; ++ind) {
        int current;
        std::cin >> current;
        std::string text;
        if (dictionary.count(current) == 0) {
            text = dictionary[previous] + ch;
        } else {
            text = dictionary[current];
        }
        std::cout << text;
        ch = text[0];
        dictionary.emplace(dictionary.size(), dictionary[previous] + text[0]);
        previous = current;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    algorithmLZWDecode();

    return 0;
}
