#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

std::vector<std::pair<std::pair<int, int>, int>> createGraph(int vertexes, int edges) {
    std::vector<std::pair<std::pair<int, int>, int>> graph;
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.push_back(std::make_pair(std::make_pair(from, to), weight));
    }

    return graph;
}

std::vector<int64_t> getDistances(const std::vector<std::pair<std::pair<int, int>, int>>& graph,
                                  int vertexes) {
    std::vector<int64_t> distance(vertexes, INT64_MAX);
    std::vector<int> path(vertexes, -1);

    distance[0] = 0;
    int size = graph.size();
    int ind;
    for (int vertex = 0; vertex < vertexes; ++vertex) {
        ind = -1;
        for (int edge = 0; edge < size; ++edge) {
            int64_t from = graph[edge].first.first;
            int64_t to = graph[edge].first.second;
            int weight = graph[edge].second;
            if (distance[from] < INT64_MAX) {
                if (distance[from] + weight < distance[to]) {
                    distance[to] = std::max(distance[from] + weight, INT64_MIN);
                    ind = to;
                    path[to] = from;
                }
            }
        }
    }

    if (ind != -1) {
        int cycle_ind = ind;
        for (int i = 0; i < vertexes; ++i) {
            cycle_ind = path[cycle_ind];
        }

        bool flag = false;
        int current = cycle_ind;
        while (!(current == cycle_ind && flag)) {
            distance[current] = INT64_MIN;
            flag = true;
        }

        flag = false;
        while (!flag) {
            for (int j = 0; j < size; ++j) {
                int64_t from = graph[j].first.first;
                int64_t to = graph[j].first.second;
                if (distance[from] == INT64_MIN && distance[to] != INT64_MIN) {
                    distance[to] = INT64_MIN;
                    flag = true;
                }
            }
            if (!flag) {
                break;
            }
            flag = false;
        }
    }

    return distance;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int vertexes, edges;
    std::cin >> vertexes >> edges;
    std::vector<std::pair<std::pair<int, int>, int>> graph = createGraph(vertexes, edges);
    std::vector<int64_t> distance = getDistances(graph, vertexes);
    for (int i = 1; i < vertexes; ++i) {
        if (distance[i] == INT64_MIN) {
            std::cout << "-inf\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }

    return 0;
}
