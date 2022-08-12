#include "binary_heap_sort.h"

// Сортировка с помощью бинарного дерева.

void fixSubHeap(std::vector<int>* heap, int current_root) {
    int left_child;
    int right_child;
    int smaller_child = current_root;

    while (current_root < (int)heap->size()) {
        left_child = current_root * 2 + 1;
        right_child = current_root * 2 + 2;
        smaller_child = current_root;

        if (left_child < (int)heap->size() && heap->at(smaller_child) > heap->at(left_child)) {
            smaller_child = left_child;
        }
        if (right_child < (int)heap->size() && heap->at(smaller_child) > heap->at(right_child)) {
            smaller_child = right_child;
        }

        if (smaller_child == current_root) {
            break;
        }
        std::swap(heap->at(current_root), heap->at(smaller_child));
        current_root = smaller_child;
    }
}

void add(std::vector<int>* heap, int element) {
    heap->push_back(element);
    int current = heap->size() - 1;
    int parent = (current - 1) / 2;

    while (current > 0 && heap->at(parent) > heap->at(current)) {
        std::swap(heap->at(parent), heap->at(current));
        current = parent;
        parent = (current - 1) / 2;
    }
}

int extract(std::vector<int>* heap) {
    int min_element = heap->front();
    heap->front() = heap->back();
    heap->pop_back();
    fixSubHeap(heap, 0);

    return min_element;
}

void binaryHeapSort(std::vector<int>* array) {
    std::vector<int> heap;
    for (int element : *array) {
        add(&heap, element);
    }

    array->clear();
    while (!heap.empty()) {
        array->push_back(extract(&heap));
    }
}
