#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<pair<int, int>> edges; // Store all edges

    // Find function for Union-Find
    int find(int parent[], int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent, parent[i]);
    }

    // Union function for Union-Find
    void unionSets(int parent[], int rank[], int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (xroot != yroot) {
            if (rank[xroot] < rank[yroot])
                parent[xroot] = yroot;
            else if (rank[xroot] > rank[yroot])
                parent[yroot] = xroot;
            else {
                parent[yroot] = xroot;
                rank[xroot]++;
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
    }

    void addEdge(int u, int v) {
        edges.push_back({u, v});
    }

    void removeCycles() {
        vector<pair<int, int>> result; // To store the edges of the graph without cycles
        int parent[V], rank[V];
        fill(parent, parent + V, 0);
        fill(rank, rank + V, 0);

        for (int i = 0; i < V; i++)
            parent[i] = i;

        for (auto edge : edges) {
            int u = edge.first;
            int v = edge.second;

            int x = find(parent, u);
            int y = find(parent, v);

            if (x != y) {
                result.push_back(edge);
                unionSets(parent, rank, x, y);
            }
        }

        cout << "Graph after removing cycles:" << endl;
        for (auto edge : result) {
            cout << edge.first << " - " << edge.second << endl;
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // This edge creates a cycle
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1); // This edge creates another cycle

    g.removeCycles();

    return 0;
}
