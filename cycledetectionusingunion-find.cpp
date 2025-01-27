#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<pair<int, int>> edges;  // Edge list

    int find(int i, vector<int>& parent) {
        if (parent[i] == -1) {
            return i;
        }
        return parent[i] = find(parent[i], parent);
    }

    void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
        int uRoot = find(u, parent);
        int vRoot = find(v, parent);

        if (uRoot != vRoot) {
            if (rank[uRoot] < rank[vRoot]) {
                parent[uRoot] = vRoot;
            } else if (rank[uRoot] > rank[vRoot]) {
                parent[vRoot] = uRoot;
            } else {
                parent[vRoot] = uRoot;
                rank[uRoot]++;
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

    bool isCyclic() {
        vector<int> parent(V, -1);
        vector<int> rank(V, 0);

        for (auto edge : edges) {
            int u = edge.first;
            int v = edge.second;

            int uRoot = find(u, parent);
            int vRoot = find(v, parent);

            if (uRoot == vRoot) {
                return true;
            }

            unionSet(uRoot, vRoot, parent, rank);
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
