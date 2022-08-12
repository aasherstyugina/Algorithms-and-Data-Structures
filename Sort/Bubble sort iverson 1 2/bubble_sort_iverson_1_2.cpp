#include "bubble_sort_iverson_1_2.h"

// ���������� ��������� � �������� ��������� 1+2:
// ���������� ������ ���������� swap  � ���������� last_swap,
// � � ������ ����������� �������� ��������� �������� �� 0 �� last_swap - 1,
// ��� ��� ����� last_swap ��� ��� �������������. ���������� ������� ��������� 1,
// ���� �� ��������� �� ������ ������ �� ����� ��������, �� ���� ������ ������������.

void bubbleSortIverson12(std::vector<int>* array) {
    int length = array->size();
    int outer_ind = 0;
    int last_swap = length - 1;
    bool outer_flag = true;
    while (outer_flag && last_swap != 0) {
        outer_flag = false;
        int current_swap = 0;
        for (int inner_ind = 0; inner_ind < last_swap; ++inner_ind) {
            if (array->at(inner_ind) > array->at(inner_ind + 1)) {
                std::swap(array->at(inner_ind), array->at(inner_ind + 1));
                outer_flag = true;
                current_swap = inner_ind;
            }
        }
        ++outer_ind;
        last_swap = current_swap;
    }
}
