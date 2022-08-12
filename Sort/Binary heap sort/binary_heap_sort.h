#pragma once

#include <vector>
#include <utility>

void fixSubHeap(std::vector<int>* heap, int current_root);

void add(std::vector<int>* heap, int element);

int extract(std::vector<int>* heap);

void binaryHeapSort(std::vector<int>* array);
