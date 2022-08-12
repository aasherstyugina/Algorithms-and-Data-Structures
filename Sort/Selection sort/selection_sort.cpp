#include "selection_sort.h"

// Сортировка выбором: ищем минимальный элемент и ставим его на первое место. После этого
// аналогично поступаем с оставшейся неотсортированной частью, исключив из рассмотрения
// отсортированное начало.

void selectionSort(std::vector<int>* array) {
    int length = array->size();
    for (int outer = 0; outer < length - 1; ++outer) {
        int min_ind = outer;
        for (int inner = outer + 1; inner < length; ++inner) {
            if (array->at(inner) < array->at(min_ind)) {
                min_ind = inner;
            }
        }
        if (min_ind != outer) {
            std::swap(array->at(outer), array->at(min_ind));
        }
    }
}
