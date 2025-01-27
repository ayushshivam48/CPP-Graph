#include <iostream>
#include <vector>
#include <stack>
#include<algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list
    vector<vector<int>> allCycles;  // Store all detected cycles

    void DFSUtil(int v, vector<bool>& visited, vector<bool>& recStack, stack<int>& path) {
        visited[v] = true;
        recStack[v] = true;
        path.push(v);

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, recStack, path);
            } else if (recStack[neighbor]) {
                // A cycle is detected, backtrack to find the cycle
                vector<int> cycle;
                stack<int> tempPath = path;
                while (!tempPath.empty()) {
                    int node = tempPath.top();
                    cycle.push_back(node);
                    tempPath.pop();
                    if (node == neighbor) break;
                }
                reverse(cycle.begin(), cycle.end());
                allCycles.push_back(cycle);
            }
        }

        path.pop();
        recStack[v] = false;
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void findAllCycles() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);
        stack<int> path;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited, recStack, path);
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
