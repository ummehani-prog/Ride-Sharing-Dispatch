#include "City.h"
#include <climits>

City::City() {}

int City::findNodeIndex(const string& name) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name)
            return i;
    }
    return -1;
}

void City::addLocation(const string& name) {
    if (findNodeIndex(name) == -1) { 
        Node n;
        n.name = name;
        nodes.push_back(n);
    }
}

void City::addRoad(const string& from, const string& to, int distance) {
    addLocation(from);
    addLocation(to);
    int u = findNodeIndex(from);
    int v = findNodeIndex(to);
    nodes[u].edges.push_back({to, distance});
    nodes[v].edges.push_back({from, distance});
}

// Custom Min Heap implementation
struct HeapNode {
    int dist;
    int u;
    bool operator>(const HeapNode& other) const {
        return dist > other.dist;
    }
};

class CustomMinHeap {
private:
    vector<HeapNode> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].dist > heap[index].dist) {
                swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left].dist < heap[smallest].dist)
                smallest = left;
            if (right < size && heap[right].dist < heap[smallest].dist)
                smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void push(int dist, int u) {
        heap.push_back({dist, u});
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    HeapNode top() {
        return heap.front();
    }

    bool empty() {
        return heap.empty();
    }
};

int City::shortestPath(const string& src, const string& dest) {
    if (src == dest) return 0;
    
    int n = nodes.size();
    vector<int> dist(n, INT_MAX);
    int start = findNodeIndex(src);
    int end = findNodeIndex(dest);
    
    if (start == -1 || end == -1) return -1;

    dist[start] = 0;
    
    // Use Custom Min Heap
    CustomMinHeap pq;
    pq.push(0, start);

    while (!pq.empty()) {
        HeapNode top = pq.top();
        pq.pop();
        
        int d = top.dist;
        int u = top.u;

        if (d > dist[u]) continue;
        if (u == end) return dist[u];

        for (auto &edge : nodes[u].edges) {
            int v = findNodeIndex(edge.to);
            if (v != -1 && dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
                pq.push(dist[v], v);
            }
        }
    }

    return (dist[end] == INT_MAX) ? -1 : dist[end];
}


