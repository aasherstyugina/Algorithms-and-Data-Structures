#include "insertion_bin_sort.h"

// Сортировка бинарными вставками: каждый очередной элемент вставляется в нужное место
// среди ранее упорядоченных. Место ищется с помощью бинарного поиска.

int binarySearch(std::vector<int>* array, int key, int left, int right) {
    while (left < right - 1) {
        int mid = left + (right - left) / 2;
        if (array->at(mid) <= key) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

void insertionBinSort(std::vector<int>* array) {
    int length = array->size();
    for (int outer = 1; outer < length; ++outer) {
        int current = array->at(outer);
        int insert_ind = binarySearch(array, array->at(outer), -1, outer);
        if (insert_ind != outer - 1) {
            int inner = outer - 1;
            while (inner > insert_ind) {
                std::swap(array->at(inner), array->at(inner + 1));
                --inner;
            }
            array->at(insert_ind + 1) = current;
        }
    }
}
