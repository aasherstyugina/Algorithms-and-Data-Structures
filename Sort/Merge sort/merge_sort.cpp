#include "merge_sort.h"

// Итеративная сортировка слиянием. Массив делится на два подмассива, подмассивы сортируются
// (тоже с помощью данной сортировки), затем сливаются в один массив следующим образом:
// элементы подмассивов поочередно сравниваются, меньший записывается в результат. 
// Процесс происходит до тех пор, пока в обоих подмассивах есть непросмотренные элементы.
// Когда это условие нарушается, остаток не до конца просмотренного массива целиком 
// записывается в результат.

void mergeTwoArrays(std::vector<int>* array, int left, int mid, int right) {
    std::vector<int> merge;
    int left_ind = left, right_ind = mid + 1;

    while (left_ind <= mid && right_ind <= right) {
        int first = array->at(left_ind);
        int second = array->at(right_ind);
        if (first <= second) {
            merge.push_back(first);
            ++left_ind;
        } else {
            merge.push_back(second);
            ++right_ind;
        }
    }

    if (left_ind <= mid) {
        int rest = right - (mid - left_ind);
        for (int ind = right; ind >= rest; --ind) {
            array->at(ind) = array->at(mid);
            --mid;
        }
    }
    int num_ind = left;
    for (int num : merge) {
        array->at(num_ind) = num;
        ++num_ind;
    }
}

void mergeSort(std::vector<int>* array) {
    int length = array->size();
    if (length <= 1) {
        return;
    }

    for (int size = 1; size < length; size *= 2) {
        for (int left = 0; left < length - 1; left += size * 2) {
            int mid = std::min(left + size - 1, length - 1);
            int right = std::min(left + size * 2 - 1, length - 1);
            mergeTwoArrays(array, left, mid, right);
        }
    }
}
