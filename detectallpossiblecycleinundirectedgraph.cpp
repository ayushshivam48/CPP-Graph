#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list
    vector<vector<int>> allCycles;  // Store all detected cycles

    void DFSUtil(int v, int parent, vector<bool>& visited, vector<int>& path) {
        visited[v] = true;
        path.push_back(v);

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, v, visited, path);
            } else if (neighbor != parent) {
                // A cycle is detected, backtrack to find the cycle
                vector<int> cycle;
                auto it = find(path.begin(), path.end(), neighbor);
                if (it != path.end()) {
                    cycle.insert(cycle.end(), it, path.end());
                    cycle.push_back(neighbor);  // Complete the cycle
                    allCycles.push_back(cycle);
                }
            }
        }

        path.pop_back();
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // Undirected graph
    }

    void findAllCycles() {
        vector<bool> visited(V, false);
        vector<int> path;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, -1, visited, path);
            }
        }

        // Print all detected cycles
        for (const auto& cycle : allCycles) {
            cout << "Cycle: ";
            for (int node : cycle) {
                cout << node << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);

    g.findAllCycles();

    return 0;
}
