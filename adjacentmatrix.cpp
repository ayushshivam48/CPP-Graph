#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // Comment this for directed graph
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();

    return 0;
}
