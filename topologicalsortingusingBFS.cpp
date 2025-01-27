/*“Kahn's algorithm is a method used for topological sorting of a Directed Acyclic Graph (DAG). 
It’s a breadth-first search (BFS)-based algorithm that produces a linear ordering of vertices 
such that for every directed edge u→v, vertex u comes before vertex v in the ordering." */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Directed edge from u to v
    }

    void topologicalSort() {
        vector<int> inDegree(V, 0); // In-degree of each vertex

        // Calculate in-degree (number of incoming edges) for each vertex
        for (int u = 0; u < V; u++) {
            for (int v : adjList[u]) {
                inDegree[v]++;
            }
        }

        // Queue for vertices with in-degree 0
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Perform BFS
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);

            for (int v : adjList[u]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Check if there was a cycle (i.e., not a DAG)
        if (topoOrder.size() != V) {
            cout << "The graph is not a DAG (it contains a cycle)." << endl;
            return;
        }

        // Print the topological order
        cout << "Topological Order: ";
        for (int v : topoOrder) {
            cout << v << " ";
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
