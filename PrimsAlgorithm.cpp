#include <iostream>
#include <cmath>

const int V = 5;

// Finds the vertex with the minimum key value
// among vertices not yet included in the MST.
int minKey(double key[], bool mstSet[]) {
    double min = INFINITY;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Prints the MST and calculates its total weight.
void printMST(int parent[], double graph[V][V]) {
    std::cout << "Edge\tWeight\n";

    double totalWeight = 0;

    for (int i = 1; i < V; i++) {
        char u = 'a' + parent[i];
        char v = 'a' + i;

        std::cout << u << " - " << v << "\t"
                  << graph[i][parent[i]] << "\n";

        totalWeight += graph[i][parent[i]];
    }

    std::cout << "--------------------\n";
    std::cout << "Total MST Weight: " << totalWeight << "\n";
}

// Constructs the MST using an adjacency matrix.
void primMST(double graph[V][V]) {
    int parent[V];
    double key[V];
    bool mstSet[V];

    // Initialize the arrays.
    for (int i = 0; i < V; i++) {
        key[i] = INFINITY;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Start with vertex a (index 0).
    key[0] = 0;

    for (int count = 0; count < V; count++) {
        int u = minKey(key, mstSet);

        // Check whether the graph is disconnected.
        if (u == -1) {
            std::cout << "Error: The graph is disconnected.\n";
            return;
        }

        mstSet[u] = true;

        // Update the keys of adjacent vertices.
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 &&
                mstSet[v] == false &&
                graph[u][v] < key[v]) {

                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    // Vertices: a=0, b=1, c=2, d=3, e=4.
    // A weight of 0 represents the absence of an edge.

    double graph[V][V] = {
        { 0, 5, 7, 0, 2 },
        { 5, 0, 0, 6, 3 },
        { 7, 0, 0, 4, 4 },
        { 0, 6, 4, 0, 5 },
        { 2, 3, 4, 5, 0 }
    };

    primMST(graph);

    return 0;
}
