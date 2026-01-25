#ifndef CITY_H
#define CITY_H
#include <vector>
#include <string>
using namespace std;
// Graph edge structure
struct Edge {
    string to;
    int weight;
};
// Graph node
struct Node {
    string name;
    vector<Edge> edges;
};
// City graph class
class City {
private:
    vector<Node> nodes;
    int findNodeIndex(const string& name);

public:
    City();
    void addLocation(const string& name);
    void addRoad(const string& from, const string& to, int distance);
    int shortestPath(const string& src, const string& dest);
};

#endif