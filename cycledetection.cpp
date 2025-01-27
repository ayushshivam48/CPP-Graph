#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list

    bool DFSUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor] && DFSUtil(neighbor, visited, recStack)) {
                return true;
            } else if (recStack[neighbor]) {
                return true;
            }
        }

        recStack[v] = false;  // Remove the vertex from the recursion stack
        return false;
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    bool isCyclic() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i] && DFSUtil(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);

    if (g.isCyclic()) {
        cout << "Graph contains a cycle" << endl;
    } else {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
