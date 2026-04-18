#include <gtest/gtest.h>

#include "graph_demo.h"

TEST(GraphDemoTest, BFS) {
    std::vector<std::vector<int>> adj = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    EXPECT_EQ(bfs_shortest(adj, 0, 3), 2);
    EXPECT_EQ(bfs_shortest(adj, 0, 0), 0);
}
TEST(GraphDemoTest, DFSConnected) {
    std::vector<std::vector<int>> adj = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    EXPECT_TRUE(dfs_connected(adj, 0, 3));
}
TEST(GraphDemoTest, Dijkstra) {
    std::vector<std::vector<std::pair<int, int>>> graph(4);
    graph[0] = {{1, 4}, {2, 1}};
    graph[1] = {{3, 1}};
    graph[2] = {{1, 2}, {3, 5}};
    auto dist = dijkstra(graph, 0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 3);
    EXPECT_EQ(dist[3], 4);
}
TEST(GraphDemoTest, TopologicalSort) {
    std::vector<std::vector<int>> dag = {{1, 2}, {3}, {3}, {}};
    auto topo = topological_sort(dag);
    EXPECT_EQ(topo.size(), 4u);
    // 0 must come before 1 and 2
    EXPECT_EQ(topo[0], 0);
}
