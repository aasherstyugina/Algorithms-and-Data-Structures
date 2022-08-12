#pragma once

#include <vector>
#include <cmath>

int digit(int number, int index);

int maxDigit(int number);

int findMaxDigit(const std::vector<int>& array);

void radixSort(std::vector<int>* array);