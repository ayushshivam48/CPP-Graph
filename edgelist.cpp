#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int V;
    vector<pair<int, int>> edgeList;

    Graph(int V) {
        this->V = V;
    }

    void addEdge(int u, int v) {
        edgeList.push_back({u, v});
    }

    void printGraph() {
        for (auto edge : edgeList) {
            cout << "(" << edge.first << ", " << edge.second << ")" << endl;
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
