/*Dijkstra's algorithm is a classic method used to find the shortest paths 
from a source vertex to all other vertices in a graph with non-negative weights.*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

// Function to perform Dijkstra's algorithm
void dijkstra(const vector<vector<pair<int, int>>>& adjList, int source, vector<int>& distances, vector<int>& predecessors) {
    int V = adjList.size();
    distances.assign(V, INT_MAX);  // Initialize distances with infinity
    predecessors.assign(V, -1);    // Initialize predecessors with -1
    distances[source] = 0;         // Distance to source is 0

    // Min-Heap priority queue to store (distance, vertex) pairs
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});     // Start with the source vertex

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        int dist_u = minHeap.top().first;
        minHeap.pop();

        // If this distance is greater than the recorded distance, skip
        if (dist_u > distances[u]) continue;

        // Explore neighbors
        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Check if a shorter path to v is found
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;     // Update predecessor
                minHeap.push({distances[v], v});
            }
        }
    }
}

// Function to print the path from source to target
void printPath(int target, const vector<int>& predecessors) {
    if (target == -1) {
        cout << "No path";
        return;
    }

    stack<int> path;
    for (int v = target; v != -1; v = predecessors[v]) {
        path.push(v);
    }

    while (!path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
}

// Function to print shortest distance and paths from source
void printResults(int source, const vector<int>& distances, const vector<int>& predecessors) {
    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Vertex " << i << ": " << (distances[i] == INT_MAX ? "INF" : to_string(distances[i])) << " ";
        cout << "Path: ";
        if (distances[i] != INT_MAX) {
            printPath(i, predecessors);
        } else {
            cout << "No path";
        }
        cout << endl;
    }
}

int main() {
    int V = 9;  // Number of vertices
    vector<vector<pair<int, int>>> adjList(V);

    // Example graph
    adjList[0].emplace_back(1, 4);
    adjList[0].emplace_back(7, 8);
    adjList[1].emplace_back(2, 8);
    adjList[1].emplace_back(7, 11);
    adjList[2].emplace_back(3, 7);
    adjList[2].emplace_back(5, 4);
    adjList[2].emplace_back(8, 2);
    adjList[3].emplace_back(4, 9);
    adjList[3].emplace_back(5, 14);
    adjList[4].emplace_back(5, 10);
    adjList[5].emplace_back(6, 2);
    adjList[6].emplace_back(7, 1);
    adjList[6].emplace_back(8, 6);
    adjList[7].emplace_back(8, 7);

    vector<int> distances;
    vector<int> predecessors;
    int source = 0;  // Source vertex

    dijkstra(adjList, source, distances, predecessors);

    // Print the shortest distances and paths from the source vertex
    printResults(source, distances, predecessors);

    return 0;
}
