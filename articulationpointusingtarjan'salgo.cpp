/*An articulation point (or cut vertex) in a graph is a vertex which, 
when removed, increases the number of connected components in the graph. 
In other words, removing an articulation point disconnects the graph.*/
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list
    vector<int> disc; // Discovery times of visited vertices
    vector<int> low; // Lowest discovery times reachable from vertex
    vector<bool> ap; // To store articulation points
    int time; // Time variable used during DFS

    void APUtil(int u, vector<int>& parent) {
        int children = 0;
        disc[u] = low[u] = ++time;
        
        for (int v : adj[u]) {
            if (disc[v] == -1) { // If v is not visited
                children++;
                parent[v] = u;
                APUtil(v, parent);
                
                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 && children > 1) {
                    ap[u] = true;
                }
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    ap[u] = true;
                }
            } else if (v != parent[u]) { // Update low value of u for parent function calls
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        disc.assign(V, -1);
        low.assign(V, -1);
        ap.assign(V, false);
        time = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void findArticulationPoints() {
        vector<int> parent(V, -1);

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                APUtil(i, parent);
            }
        }

        // Print all articulation points
        cout << "Articulation Points in the graph:" << endl;
        for (int i = 0; i < V; i++) {
            if (ap[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    g.findArticulationPoints();

    return 0;
}
