#include "counting_sort.h"

// Устойчивая сортировка подсчетом с использованием вспомогательных массивов
// для счетчика и для отсортированного массива.

void findMinMax(int* min, int* max, const std::vector<int>& array) {
    for (int element : array) {
        if (element < *min) {
            *min = element;
        }
        if (element > *max) {
            *max = element;
        }
    }
}

void countingSort(std::vector<int>* array) {
    int length = array->size();
    int min = INT32_MAX;
    int max = INT32_MIN;
    findMinMax(&min, &max, *array);

    std::vector<int> counter(max - min + 1);
    for (int i = 0; i < length; ++i) {
        ++counter[array->at(i) - min];
    }
    for (int i = 1; i < max - min + 1; ++i) {
        counter[i] += counter[i - 1];
    }

    std::vector<int> result(length);
    for (int i = length - 1; i >= 0; --i) {
        result[counter[array->at(i) - min] - 1] = array->at(i);
        --counter[array->at(i) - min];
    }

    array->clear();
    array = &result;
}
