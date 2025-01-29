/*Prim's Algorithm starts from an arbitrary vertex and 
expands the MST by adding the smallest edge that connects 
a vertex in the MST to a vertex outside it.*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> iPair;

void prim(int V, vector<vector<iPair>>& adj) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    int src = 0; // Starting from vertex 0

    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    pq.push({0, src});
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    int total_weight = 0;
    cout << "Prim's MST:" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " : " << key[i] << endl;
        total_weight += key[i];
    }
    cout << "Total Weight: " << total_weight << endl;
}

int main() {
    int V = 4;
    vector<vector<iPair>> adj(V);

    adj[0].push_back({1, 10});
    adj[0].push_back({2, 6});
    adj[0].push_back({3, 5});
    adj[1].push_back({0, 10});
    adj[1].push_back({3, 15});
    adj[2].push_back({0, 6});
    adj[2].push_back({3, 4});
    adj[3].push_back({0, 5});
    adj[3].push_back({1, 15});
    adj[3].push_back({2, 4});

    prim(V, adj);

    return 0;
}
