#include "quick_sort_lomuto.h"

// Быстрая сортировка с разбиением Ломуто. Опорный элемент - последний. Храним индекс в left.
// Просматриваем массив с начала. Если встречается элемент <= опорного, то вставляем его
// перед опорным и увеличиваем индекс.

int partition(std::vector<int>* array, int left, int right) {
    int pivot = array->at(right);
    for (int ind = left; ind < right; ++ind) {
        if (array->at(ind) <= pivot) {
            std::swap(array->at(ind), array->at(left));
            ++left;
        }
    }
    std::swap(array->at(left), array->at(right));

    return left;
}

void recursiveLomuto(std::vector<int>* array, int left, int right) {
    int pivot = partition(array, left, right);
    if (left < pivot - 1) {
        recursiveLomuto(array, left, pivot - 1);
    }
    if (pivot + 1 < right) {
        recursiveLomuto(array, pivot + 1, right);
    }
}

void quickSortLomuto(std::vector<int>* array) {
    int length = array->size();
    recursiveLomuto(array, 0, length - 1);
}
