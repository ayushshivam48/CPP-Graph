#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    vector<vector<int>> findAllPathsBFS(int source, int target) {
        vector<vector<int>> allPaths;
        queue<vector<int>> q;

        q.push({source});  // Start with the source node

        while (!q.empty()) {
            vector<int> path = q.front();
            q.pop();

            int lastNode = path.back();

            if (lastNode == target) {
                allPaths.push_back(path);
            }

            for (int neighbor : adjList[lastNode]) {
                if (find(path.begin(), path.end(), neighbor) == path.end()) {
                    vector<int> newPath = path;
                    newPath.push_back(neighbor);
                    q.push(newPath);
                }
            }
        }

        return allPaths;
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
    g.addEdge(3, 5);

    int source = 0, target = 5;

    vector<vector<int>> allPaths = g.findAllPathsBFS(source, target);

    cout << "All paths from " << source << " to " << target << " are:" << endl;
    for (const auto& path : allPaths) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
