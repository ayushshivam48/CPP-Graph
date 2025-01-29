//Tarjan's Algorithm for Finding Bridges//
/*Tarjan's algorithm is a well-known algorithm in graph theory designed 
to find all strongly connected components (SCCs) in a directed graph. 
It is named after Robert Tarjan, who developed the algorithm. 
The algorithm is efficient and operates in linear time, O(V + E), 
where V is the number of vertices and E is the number of edges.*/
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    void DFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<pair<int, int>>& bridges, int& time) {
        disc[u] = low[u] = ++time;
        for (int v : adj[u]) {
            if (disc[v] == -1) { // If v is not visited
                parent[v] = u;
                DFS(v, disc, low, parent, bridges, time);
                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
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
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void findBridges() {
        vector<int> disc(V, -1); // Stores discovery times of visited vertices
        vector<int> low(V, -1);  // Stores the lowest points of vertices
        vector<int> parent(V, -1); // Parent vertices in DFS tree
        vector<pair<int, int>> bridges; // To store bridges
        int time = 0;

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                DFS(i, disc, low, parent, bridges, time);
            }
        }

        // Print all bridges
        cout << "Bridges in the graph:" << endl;
        for (const auto& bridge : bridges) {
            cout << bridge.first << " - " << bridge.second << endl;
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

    g.findBridges();

    return 0;
}
