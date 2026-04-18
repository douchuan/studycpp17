#ifndef STUDYCPP_ALGORITHM_GRAPH_DEMO_H
#define STUDYCPP_ALGORITHM_GRAPH_DEMO_H

#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// --- BFS（无权图最短路径步数） ---
inline int bfs_shortest(const std::vector<std::vector<int>>& adj, int start, int target) {
    int n = static_cast<int>(adj.size());
    std::vector<bool> visited(n, false);
    std::queue<std::pair<int, int>> q;
    q.emplace(start, 0);
    visited[start] = true;
    while (!q.empty()) {
        auto [cur, dist] = q.front();
        q.pop();
        if (cur == target) return dist;
        for (int neighbor : adj[cur]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.emplace(neighbor, dist + 1);
            }
        }
    }
    return -1;  // 不可达
}

// --- DFS（连通性检测） ---
inline bool dfs_connected(const std::vector<std::vector<int>>& adj, int start, int target) {
    int n = static_cast<int>(adj.size());
    std::vector<bool> visited(n, false);
    auto dfs = [&](auto& self, int node) -> bool {
        if (node == target) return true;
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor] && self(self, neighbor)) return true;
        }
        return false;
    };
    return dfs(dfs, start);
}

// --- Dijkstra 最短路径 ---
inline std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph,
                                 int start) {
    int n = static_cast<int>(graph.size());
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(n, INF);
    dist[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

// --- 拓扑排序 ---
inline std::vector<int> topological_sort(const std::vector<std::vector<int>>& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> indegree(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : adj[u]) indegree[v]++;
    std::queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0) q.emplace(i);
    std::vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.emplace_back(u);
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.emplace(v);
        }
    }
    return result;  // size < n 表示有环
}

#endif  // STUDYCPP_ALGORITHM_GRAPH_DEMO_H
