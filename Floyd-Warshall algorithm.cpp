#include <iostream>
#include <algorithm>

int64_t** createGraph(int vertexes, int edges) {
    int64_t** graph = new int64_t*[vertexes];
    for (int i = 0; i < vertexes; ++i) {
        graph[i] = new int64_t[vertexes];
        for (int j = 0; j < vertexes; ++j) {
            graph[i][j] = INT64_MAX;
        }
    }

    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph[from][to] = weight;
    }

    return graph;
}

int64_t** getDistances(int vertexes, int edges) {
    int64_t** graph = createGraph(vertexes, edges);

    for (int k_ind = 0; k_ind < vertexes; ++k_ind) {
        for (int i = 0; i < vertexes; ++i) {
            for (int j = 0; j < vertexes; ++j) {
                if (graph[i][k_ind] < INT64_MAX && graph[k_ind][j] < INT64_MAX) {
                    graph[i][j] = std::min(graph[i][j],
                                           static_cast<int64_t>(graph[i][k_ind] + graph[k_ind][j]));
                }
            }
        }
    }

    return graph;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int vertexes, edges;
    std::cin >> vertexes >> edges;
    int64_t** graph = getDistances(vertexes, edges);
    for (int i = 0; i < vertexes; ++i) {
        for (int j = 0; j < vertexes; ++j) {
            if (i != j) {
                int64_t weight = graph[i][j] == INT64_MAX ? -1 : graph[i][j];
                std::cout << i << " " << j << " " << weight << "\n";
            }
        }
    }

    for (int i = 0; i < vertexes; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
