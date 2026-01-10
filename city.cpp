#include "City.h"
#include <climits>  // INT_MAX ke liye
City::City() {
    // do not initialize yet
    // nodes vector itsef emphy
}
int City::findNodeIndex(const string& name) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name)
            return i; // found the index
    }
    return -1; // if do not find node
}
void City::addLocation(const string& name) {
    if (findNodeIndex(name) == -1) { 
        Node n;
        n.name = name;
        nodes.push_back(n);
    }
}
void City::addRoad(const string& from, const string& to, int distance) {
    addLocation(from); // ensure location exists
    addLocation(to);

    int u = findNodeIndex(from);
    int v = findNodeIndex(to);

    nodes[u].edges.push_back({to, distance});
    nodes[v].edges.push_back({from, distance}); // undirected graph
}
int City::shortestPath(const string& src, const string& dest) {
    int n = nodes.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    int start = findNodeIndex(src);
    if (start == -1) return -1;

    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // remaining nodes unreachable
        visited[u] = true;

        for (auto &edge : nodes[u].edges) {
            int v = findNodeIndex(edge.to);
            if (v != -1 && dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
            }
        }
    }

    int destIndex = findNodeIndex(dest);
    if (destIndex == -1 || dist[destIndex] == INT_MAX)
        return -1; // do not find the path
    return dist[destIndex];
}

