#include "graph_demo.h"

#include <iostream>

int main() {
    // 无向图: 0-1-2-3, 0-2
    std::vector<std::vector<int>> adj = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};

    std::cout << "BFS(0->3): " << bfs_shortest(adj, 0, 3) << "\n";
    std::cout << "DFS(0->3): " << std::boolalpha << dfs_connected(adj, 0, 3) << "\n";

    // 有向加权图: Dijkstra
    // 0->1(4), 0->2(1), 2->1(2), 1->3(1), 2->3(5)
    std::vector<std::vector<std::pair<int, int>>> graph(4);
    graph[0] = {{1, 4}, {2, 1}};
    graph[1] = {{3, 1}};
    graph[2] = {{1, 2}, {3, 5}};
    graph[3] = {};
    auto dist = dijkstra(graph, 0);
    std::cout << "Dijkstra from 0: ";
    for (int d : dist) std::cout << (d == std::numeric_limits<int>::max() ? -1 : d) << " ";
    std::cout << "\n";

    // 拓扑排序: 0->1, 0->2, 1->3, 2->3
    std::vector<std::vector<int>> dag = {{1, 2}, {3}, {3}, {}};
    auto topo = topological_sort(dag);
    std::cout << "topological: ";
    for (int x : topo) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
