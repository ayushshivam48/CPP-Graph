#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* next;
};

class Graph {
public:
    int V;
    vector<Node*> adjList;

    Graph(int V) {
        this->V = V;
        adjList.resize(V, nullptr);
    }

    void addEdge(int u, int v) {
        Node* newNode = new Node{v, adjList[u]};
        adjList[u] = newNode;

        // For undirected graph, add edge in the opposite direction as well
        newNode = new Node{u, adjList[v]};
        adjList[v] = newNode;
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ":";
            Node* temp = adjList[i];
            while (temp) {
                cout << " -> " << temp->value;
                temp = temp->next;
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
