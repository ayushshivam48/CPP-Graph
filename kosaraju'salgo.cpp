/*Kosaraju's Algorithm is used to find all strongly connected components (SCCs) 
in a directed graph. A strongly connected component is a maximal subgraph 
where there is a path between any pair of vertices within the component.*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    void DFS(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (int i : adj[v]) {
            if (!visited[i]) {
                DFS(i, visited, Stack);
            }
        }
        Stack.push(v);
    }

    void DFSUtil(int v, vector<bool>& visited, vector<vector<int>>& transpose) {
        visited[v] = true;
        cout << v << " ";
        for (int i : transpose[v]) {
            if (!visited[i]) {
                DFSUtil(i, visited, transpose);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void getSCCs() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        // Step 1: Fill vertices in Stack according to their finishing times
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, visited, Stack);
            }
        }

        // Step 2: Transpose the graph
        vector<vector<int>> transpose(V);
        for (int i = 0; i < V; i++) {
            for (int j : adj[i]) {
                transpose[j].push_back(i);
            }
        }

        // Step 3: Perform DFS on transposed graph in order of stack
        fill(visited.begin(), visited.end(), false);
        cout << "Strongly Connected Components:" << endl;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!visited[v]) {
                DFSUtil(v, visited, transpose);
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    g.getSCCs();

    return 0;
}
