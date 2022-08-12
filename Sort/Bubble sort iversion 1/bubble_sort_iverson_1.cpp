#include "bubble_sort_iverson_1.h"

// —ортировка пузырьком с условием јйверсона 1:
// если после работы внутреннего цикла не произошло ни одного swap,
// то массив отсортирован и можно прекратить работу.

void bubbleSortIverson1(std::vector<int>* array) {
	int length = array->size();
	int ind = 0;
	bool cycle_statement = true;
	while (cycle_statement) {
		cycle_statement = false;
		for (int i = 0; i < length - ind - 1; ++i) {
			if (array->at(i) > array->at(i + 1)) {
				std::swap(array->at(i), array->at(i + 1));
				cycle_statement = true;
			}
		}
		++ind;
	}
}
