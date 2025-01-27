#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list

    // Utility function for DFS
    void DFSUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, Stack);
            }
        }

        // Push the current vertex to the stack which stores the topological order
        Stack.push(v);
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);  // Directed edge from u to v
    }

    void topologicalSort() {
        stack<int> Stack;  // Stack to store the topological order
        vector<bool> visited(V, false);  // Mark all vertices as not visited

        // Call the recursive helper function to store Topological Sort
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited, Stack);
            }
        }

        // Print the contents of the stack (the topological order)
        cout << "Topological Order: ";
        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
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

    g.topologicalSort();

    return 0;
}
