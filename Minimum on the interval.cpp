  // Display the minimum number for each range with some length in the array.

#include <iostream>
#include <cmath>
#include <algorithm>

const int max_number = 32767;

int min_in_range(int* tree, int left_index, int right_index) {
    int min_number = max_number;
    while (left_index <= right_index) {
        if (left_index % 2 == 1) {
            min_number = std::min(min_number, tree[left_index]);
        }
        if (right_index % 2 == 0) {
            min_number = std::min(min_number, tree[right_index]);
        }
        left_index = (left_index + 1) / 2;
        right_index = (right_index - 1) / 2;
    }

    return min_number;
}

int main() {
    int amount_of_numbers, range_length;
    std::cin >> amount_of_numbers >> range_length;

    int tree_items_num = pow(2, static_cast<int>(log2(amount_of_numbers - 1) + 1));
    int* tree = new int[2 * tree_items_num];

    for (int index = 0; index < amount_of_numbers; ++index) {
        int number;
        std::cin >> number;
        tree[tree_items_num + index] = number;
    }
    for (int index = tree_items_num + amount_of_numbers; index < tree_items_num * 2; ++index) {
        tree[index] = max_number;
    }
    for (int index = tree_items_num - 1; index > 0; --index) {
        tree[index] = std::min(tree[index * 2], tree[index * 2 + 1]);
    }

    int left_index = tree_items_num, right_index = range_length + tree_items_num - 1;
    while (right_index < tree_items_num + amount_of_numbers) {
        std::cout << min_in_range(tree, left_index, right_index) << " ";
        ++left_index;
        ++right_index;
    }

    delete[] tree;
    tree = nullptr;

    return 0;
}
