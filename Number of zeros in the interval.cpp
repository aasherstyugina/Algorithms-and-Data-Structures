  // Counting the number of zeros in a range.

#include <iostream>
#include <cmath>

int zeros_counter(int* tree, int left_index, int right_index) {
    int amount_of_zeros = 0;
    while (left_index <= right_index) {
        if (left_index % 2 == 1) {
            amount_of_zeros += tree[left_index];
        }
        if (right_index % 2 == 0) {
            amount_of_zeros += tree[right_index];
        }
        left_index = (left_index + 1) / 2;
        right_index = (right_index - 1) / 2;
    }

    return amount_of_zeros;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int amount_of_numbers;
    std::cin >> amount_of_numbers;

    int tree_items_num = pow(2, static_cast<int>(log2(amount_of_numbers - 1) + 1));
    int* tree = new int[2 * tree_items_num];

    for (int index = 0; index < amount_of_numbers; ++index) {
        int number;
        std::cin >> number;
        tree[tree_items_num + index] = number == 0 ? 1 : 0;
    }
    for (int index = tree_items_num + amount_of_numbers; index < tree_items_num * 2; ++index) {
        tree[index] = 0;
    }
    for (int index = tree_items_num - 1; index > 0; --index) {
        tree[index] = tree[index * 2] + tree[index * 2 + 1];
    }

    int amount_of_requests;
    std::cin >> amount_of_requests;
    for (int index = 0; index < amount_of_requests; ++index) {
        int left_index, right_index;
        std::cin >> left_index >> right_index;
        left_index = left_index + tree_items_num - 1;
        right_index = right_index + tree_items_num - 1;

        std::cout << zeros_counter(tree, left_index, right_index) << " ";
    }

    delete[] tree;
    tree = nullptr;

    return 0;
}
