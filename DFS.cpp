#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // Comment this line for a directed graph
    }

    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;  // Mark the current node as visited
        cout << node << " ";  // Process the current node

        // Recur for all adjacent vertices that haven't been visited
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);  // To track visited nodes
        DFSUtil(start, visited);  // Call the recursive helper function
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    cout << "Depth-First Search starting from vertex 0:" << endl;
    g.DFS(0);

    return 0;
}
