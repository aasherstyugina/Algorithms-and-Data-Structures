#include "insertion_sort.h"

// Сортировка вставками: каждый очередной элемент вставляется в нужное место
// среди ранее упорядоченных.

void insertionSort(std::vector<int>* array) {
    int length = array->size();
    for (int outer = 1; outer < length; ++outer) {
        int current = array->at(outer);
        int inner = outer - 1;
        while (inner >= 0 && array->at(inner) > current) {
            std::swap(array->at(inner), array->at(inner + 1));
            --inner;
        }
        array->at(inner + 1) = current;
    }
}
