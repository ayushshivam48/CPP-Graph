#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list to store multiple edges
    vector<pair<int, int>> allEdges;  // Store all edges for later reference

    // Utility function to perform DFS and detect cycles
    bool DFSUtil(int v, vector<bool>& visited, vector<bool>& inStack, vector<pair<int, int>>& cycleEdges) {
        visited[v] = true;
        inStack[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                cycleEdges.push_back({v, neighbor});
                if (DFSUtil(neighbor, visited, inStack, cycleEdges)) {
                    return true;
                }
                cycleEdges.pop_back();
            } else if (inStack[neighbor]) {
                // Cycle detected
                cycleEdges.push_back({v, neighbor});
                return true;
            }
        }

        inStack[v] = false;
        return false;
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        allEdges.push_back({u, v});
    }

    void removeCycles() {
        vector<bool> visited(V, false);
        vector<bool> inStack(V, false);
        vector<pair<int, int>> cycleEdges;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (DFSUtil(i, visited, inStack, cycleEdges)) {
                    // Found a cycle, print and remove edges
                    cout << "Cycle detected: ";
                    for (auto& edge : cycleEdges) {
                        cout << edge.first << " -> " << edge.second << " ";
                    }
                    cout << endl;

                    // Remove the edges forming the cycle
                    // This example removes only one edge from the cycle for simplicity
                    int u = cycleEdges.back().first;
                    int v = cycleEdges.back().second;
                    auto& neighbors = adjList[u];
                    neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());

                    cycleEdges.clear();
                }
            }
        }

        // Print the graph after removing cycles
        cout << "Graph after removing cycles:" << endl;
        for (int u = 0; u < V; u++) {
            for (int v : adjList[u]) {
                cout << u << " -> " << v << endl;
            }
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(1, 2); // This edge creates a cycle
    g.addEdge(2, 4); // Additional edge for demonstration

    g.removeCycles();

    return 0;
}
