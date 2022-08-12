#include "bubble_sort.h"

// Стандартная сортировка пузырьком.

void bubbleSort(std::vector<int>* array) {
	int length = array->size();
	for (int i = 0; i < length - 1; ++i) {
		for (int j = 0; j < length - i - 1; ++j) {
			if (array->at(j) > array->at(j + 1)) {
				std::swap(array->at(j), array->at(j + 1));
			}
		}
	}
}
