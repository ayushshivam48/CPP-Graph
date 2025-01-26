#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph{
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

    void BFS(int start) {
        vector<bool> visited(V, false);  // To track visited nodes
        queue<int> q;  // Queue for BFS

        visited[start] = true;  // Mark the starting node as visited
        q.push(start);  // Enqueue the starting node

        while (!q.empty()) {
            int node = q.front();  // Get the front node from the queue
            cout << node << " ";  // Process the node
            q.pop();  // Dequeue the node

            // Enqueue all adjacent nodes that haven't been visited
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
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

    cout << "Breadth-First Search starting from vertex 0:" << endl;
    g.BFS(0);

    return 0;
}
