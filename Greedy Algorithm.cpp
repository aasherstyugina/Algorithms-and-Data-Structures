#include <iostream>
#include <vector>
#include <utility>

void insertionSort(std::vector<std::pair<double, std::pair<int, int>>>* backpack, int length) {
    for (int ind = 1; ind < length; ++ind) {
        std::pair<double, std::pair<int, int>> current = backpack->at(ind);
        for (int i = ind - 1; i >= 0; --i) {
            if (backpack->at(i).first < current.first ||
                (backpack->at(i).first == current.first &&
                 backpack->at(i).second.second <= current.second.second)) {
                std::swap(backpack->at(i), backpack->at(i + 1));
            } else {
                break;
            }
        }
    }
}

std::vector<std::pair<double, std::pair<int, int>>> readBackpack(int count) {
    std::vector<int> weights;
    for (int i = 0; i < count; ++i) {
        int weight;
        std::cin >> weight;
        weights.push_back(weight);
    }
    std::vector<int> costs;
    for (int i = 0; i < count; ++i) {
        int cost;
        std::cin >> cost;
        costs.push_back(cost);
    }

    std::vector<std::pair<double, std::pair<int, int>>> pairs;
    for (int i = 0; i < count; ++i) {
        pairs.push_back(
            std::make_pair((costs[i] + 0.0) / weights[i], std::make_pair(costs[i], weights[i])));
    }

    weights.clear();
    costs.clear();

    insertionSort(&pairs, count);

    return pairs;
}

void packBackpack(const std::vector<std::pair<double, std::pair<int, int>>>& backpack, int weight) {
    int current_weight = 0;
    int64_t current_cost = 0;
    std::vector<int> index;
    int backpack_size = backpack.size();
    for (int ind = 0; ind < backpack_size; ++ind) {
        if (current_weight + backpack[ind].second.second <= weight) {
            index.push_back(ind);
            current_weight += backpack[ind].second.second;
            current_cost += backpack[ind].second.first;
        }

        if (current_weight == weight) {
            break;
        }
    }
    std::cout << current_cost << "\n";
    std::cout << current_weight << "\n";
    std::cout << index.size() << "\n";
    int count = index.size();
    for (int i = 0; i < count; ++i) {
        std::cout << backpack[index[i]].second.second << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < count; ++i) {
        std::cout << backpack[index[i]].second.first << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int count, total_weight;
    std::cin >> count >> total_weight;

    packBackpack(readBackpack(count), total_weight);

    return 0;
}
