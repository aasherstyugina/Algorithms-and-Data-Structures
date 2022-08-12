#include "quick_sort_hoare.h"

// ������� ���������� � �������������� ��������� �����. ������� ������� - �����������.
// ������ ��������������� � ������ � � �����, �������� �� ��������� �� ��� ���,
// ���� ����� ������ �� ����� ��������� �� ������� > ��������, � ������ - ��
// ������� < ��������. ������ �������� �������. ������� ������������, ���� ������� �� �����������.
// ���������� ��������� ���������� ��� �����������.

void recursiveHoare(std::vector<int>* array, int left, int right) {
    int left_ind = left, right_ind = right;
    int mid = left + (right - left) / 2;
    int pivot = array->at(mid);
    while (left_ind <= right_ind) {
        while (array->at(left_ind) < pivot) {
            ++left_ind;
        }
        while (array->at(right_ind) > pivot) {
            --right_ind;
        }
        if (left_ind > right_ind) {
            break;
        }

        std::swap(array->at(left_ind++), array->at(right_ind--));
    }

    if (left < right_ind) {
        recursiveHoare(array, left, right_ind);
    }
    if (left_ind < right) {
        recursiveHoare(array, left_ind, right);
    }
}

void quickSortHoare(std::vector<int>* array) {
    int length = array->size();
    recursiveHoare(array, 0, length - 1);
}
