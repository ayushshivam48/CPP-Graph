/*Kruskal's Algorithm starts by sorting all edges by their weights and 
then adds the smallest edges to the MST, ensuring no cycles are formed.*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int findSet(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v], parent);
}

void unionSets(int a, int b, vector<int>& parent, vector<int>& rank) {
    a = findSet(a, parent);
    b = findSet(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

void kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    vector<int> parent(V);
    vector<int> rank(V, 0);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    vector<Edge> mst;
    for (Edge e : edges) {
        if (findSet(e.u, parent) != findSet(e.v, parent)) {
            mst.push_back(e);
            unionSets(e.u, e.v, parent, rank);
        }
    }

    int total_weight = 0;
    cout << "Kruskal's MST:" << endl;
    for (Edge e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
        total_weight += e.weight;
    }
    cout << "Total Weight: " << total_weight << endl;
}

int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskal(V, edges);

    return 0;
}
