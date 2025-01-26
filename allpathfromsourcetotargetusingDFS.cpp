#include <iostream>
#include <vector>
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

    void findAllPathsUtil(int source, int target, vector<bool>& visited, vector<int>& path, vector<vector<int>>& allPaths) {
        visited[source] = true;
        path.push_back(source);

        if (source == target) {
            allPaths.push_back(path);
        } else {
            for (int neighbor : adjList[source]) {
                if (!visited[neighbor]) {
                    findAllPathsUtil(neighbor, target, visited, path, allPaths);
                }
            }
        }

        // Backtrack
        path.pop_back();
        visited[source] = false;
    }

    vector<vector<int>> findAllPaths(int source, int target) {
        vector<vector<int>> allPaths;
        vector<int> path;
        vector<bool> visited(V, false);

        findAllPathsUtil(source, target, visited, path, allPaths);

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

    vector<vector<int>> allPaths = g.findAllPaths(source, target);

    cout << "All paths from " << source << " to " << target << " are:" << endl;
    for (const auto& path : allPaths) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
