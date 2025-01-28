#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

void printPath(int target, const vector<int>& predecessors) {
    if (target == -1) {
        cout << "No path";
        return;
    }

    vector<int> path;
    for (int v = target; v != -1; v = predecessors[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
}

void bellmanFord(int V, int E, vector<Edge>& edges, int source, int target) {
    vector<int> distances(V, INT_MAX);
    vector<int> predecessors(V, -1);
    distances[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < E; ++j) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].weight;
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            cout << "Graph contains a negative weight cycle." << endl;
            return;
        }
    }

    // Print the shortest path and distance to the target
    cout << "Shortest distance from " << source << " to " << target << " is " << distances[target] << endl;
    cout << "Path: ";
    printPath(target, predecessors);
}

int main() {
    int V = 5;  // Number of vertices
    int E = 8;  // Number of edges
    vector<Edge> edges(E);

    // Example graph
    edges[0] = {0, 1, -1};
    edges[1] = {0, 2, 4};
    edges[2] = {1, 2, 3};
    edges[3] = {1, 3, 2};
    edges[4] = {1, 4, 2};
    edges[5] = {3, 2, 5};
    edges[6] = {3, 1, 1};
    edges[7] = {4, 3, -3};

    int source = 0;
    int target = 3;  // Define the target vertex

    bellmanFord(V, E, edges, source, target);

    return 0;
}
