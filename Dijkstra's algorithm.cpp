#include <iostream>
#include <vector>
#include <utility>
#include <set>

std::vector<std::vector<std::pair<int, int>>> createGraph(int vertexes, int edges) {
    std::vector<std::vector<std::pair<int, int>>> graph(vertexes);
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph[from].push_back(std::make_pair(to, weight));
    }
    return graph;
}

std::vector<int64_t> getDistances(const std::vector<std::vector<std::pair<int, int>>>& graph,
                                  int vertexes) {
    std::vector<int64_t> distance(vertexes, INT64_MAX);
    std::set<std::pair<int, int>> queue;

    distance[0] = 0;
    queue.emplace(0, 0);
    while (!queue.empty()) {
        int min_ind = queue.begin()->second;
        queue.erase(queue.begin());

        int size = graph[min_ind].size();
        for (int i = 0; i < size; ++i) {
            int64_t to = graph[min_ind][i].first;
            int weight = graph[min_ind][i].second;
            if (distance[min_ind] + weight < distance[to]) {
                distance[to] = distance[min_ind] + weight;
                queue.emplace(distance[to], to);
            }
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
    std::vector<std::vector<std::pair<int, int>>> graph = createGraph(vertexes, edges);
    std::vector<int64_t> distance = getDistances(graph, vertexes);
    for (int i = 1; i < vertexes; ++i) {
        std::cout << distance[i] << "\n";
    }

    return 0;
}
