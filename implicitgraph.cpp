#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int rows, cols;
    vector<vector<int>> grid;

    Graph(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        grid.resize(rows, vector<int>(cols, 0));
    }

    void addEdge(int x1, int y1, int x2, int y2) {
        // Since it's a grid, we just set values if needed
        // In this implicit graph, edges are represented by adjacency of cells
        grid[x1][y1] = 1;
        grid[x2][y2] = 1;
    }

    void printGraph() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int rows = 5, cols = 5;
    Graph g(rows, cols);

    g.addEdge(0, 0, 0, 1);
    g.addEdge(1, 1, 1, 2);
    g.addEdge(2, 2, 2, 3);
    g.addEdge(3, 3, 3, 4);
    g.addEdge(4, 4, 4, 3);

    g.printGraph();

    return 0;
}
