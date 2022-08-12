#include <iostream>

struct Edge {
    int first;
    int second;
    int weight;

    Edge(int first, int second, int weight) {
        this->first = first;
        this->second = second;
        this->weight = weight;
    }
};

class DSU {
public:
    explicit DSU(int length) {
        length_ = length;
        parents_ = new int[length];
        size_ = new int[length];
        for (int index = 0; index < length; ++index) {
            parents_[index] = index;
            size_[index] = 0;
        }
    }

    int find(int number) {
        if (parents_[number] == number) {
            return number;
        } else {
            return parents_[number] = find(parents_[number]);
        }
    }

    void unite(int first, int second) {
        first = find(first);
        second = find(second);

        if (first == second) {
            return;
        }

        if (size_[first] < size_[second]) {
            parents_[first] = second;
        } else {
            parents_[second] = first;
            if (size_[first] == size_[second]) {
                ++size_[first];
            }
        }
    }

    ~DSU() {
        delete[] parents_;
        parents_ = nullptr;
        delete[] size_;
        size_ = nullptr;
    }

private:
    int length_;
    int* parents_;
    int* size_;
};

void quickSort(Edge** edges, int length) {
    int begin = 0;
    int end = length - 1;
    Edge* middle = edges[length / 2];

    do {
        while (edges[begin]->weight < middle->weight) {
            ++begin;
        }
        while (edges[end]->weight > middle->weight) {
            --end;
        }

        if (begin <= end) {
            Edge* current = edges[begin];
            edges[begin] = edges[end];
            edges[end] = current;
            ++begin;
            --end;
        }
    } while (end >= begin);

    if (end > 0) {
        quickSort(edges, end + 1);
    }
    if (begin < length) {
        quickSort(&edges[begin], length - begin);
    }
}

int cruscal(Edge** edges, int length, DSU* dsu, int* passes) {
    int index_pass = 0;
    int total_weight = 0;
    for (int index = 0; index < length; ++index) {
        Edge* current = edges[index];
        if (dsu->find(current->first) != dsu->find(current->second)) {
            total_weight += current->weight;
            dsu->unite(current->first, current->second);
        } else if (passes) {
            passes[index_pass] = index;
            ++index_pass;
        }
    }

    return total_weight;
}

int main() {
    int vertices, edge_length;
    std::cin >> vertices >> edge_length;

    DSU* dsu_first = new DSU(vertices);
    Edge** edges = new Edge*[edge_length];
    for (int index = 0; index < edge_length; ++index) {
        int first, second, weight;
        std::cin >> first >> second >> weight;
        edges[index] = new Edge(first - 1, second - 1, weight);
    }
    quickSort(edges, edge_length);

    int* passes = new int[edge_length];
    for (int index = 0; index < edge_length; ++index) {
        passes[index] = -1;
    }
    int first_total_weight = cruscal(edges, edge_length, dsu_first, passes);

    int index = 0, second_total_weight = 0;
    while (passes[index] != -1) {
        DSU* dsu_second = new DSU(vertices);
        int current_weight = edges[passes[index]]->weight;
        dsu_second->unite(edges[passes[index]]->first, edges[passes[index]]->second);
        current_weight += cruscal(edges, edge_length, dsu_second, nullptr);
        if (second_total_weight == 0 || current_weight < second_total_weight) {
            second_total_weight = current_weight;
        }
        ++index;
        delete dsu_second;
    }

    std::cout << first_total_weight << " " << second_total_weight;

    delete dsu_first;
    delete[] passes;
    for (int index = 0; index < edge_length; ++index) {
        delete edges[index];
    }
    delete[] edges;

    return 0;
}
