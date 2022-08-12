#include "radix_sort.h"

// Цифровая сортировка по основанию 256.
// Упорядочиваем массив по разрядам, двигаясь от младших к старшим.

int digit(int number, int index) {
    return (number % static_cast<int>(std::pow(256, index))) /
        static_cast<int>(std::pow(256, index - 1));
}

int maxDigit(int number) {
    int index = 1, remainder = 1, devider = 1;
    do {
        remainder = static_cast<int>(std::pow(10, index));
        devider = static_cast<int>(std::pow(10, index - 1));
        ++index;
    } while (number / devider > 0);

    return index - 2;
}

int findMaxDigit(const std::vector<int>& array) {
    int max_digit = 1;
    for (int element : array) {
        int current_max_digit = maxDigit(element);
        if (current_max_digit > max_digit) {
            max_digit = current_max_digit;
        }
    }

    return max_digit;
}

void radixSort(std::vector<int>* array) {
    int length = array->size();
    int max_digit = findMaxDigit(*array);

    for (int current_digit = 1; current_digit <= max_digit; ++current_digit) {
        std::vector<int> counter(256);
        for (int j = 0; j < length; ++j) {
            int ind = digit(array->at(j), current_digit);
            ++counter[ind];
        }

        std::vector<int> offset(256);
        for (int j = 1; j < 256; ++j) {
            offset[j] = offset[j - 1] + counter[j - 1];
        }

        std::vector<int> result(length);
        for (int j = 0; j < length; ++j) {
            int ind = digit(array->at(j), current_digit);
            result[offset[ind]] = array->at(j);
            ++offset[ind];
        }

        *array = result;
    }
}
