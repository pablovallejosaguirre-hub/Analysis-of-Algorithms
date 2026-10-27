#include <iostream>
#include <cmath>

const int V = 5;

// Finds the unvisited vertex with the minimum distance from the source
int minDistance(double dist[], bool sptSet[]) {
    double min = INFINITY;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Reconstructs and prints the shortest path using a raw array
void printSolution(double dist[], int parent[]) {
    std::cout << "Vertex\t Distance from Source\t Path\n";
    for (int i = 0; i < V; i++) {
        char v = 'a' + i;
        std::cout << v << " \t\t " << dist[i] << " \t\t\t ";

        int path[V];
        int count = 0;
        int current = i;

        while (current != -1) {
            path[count++] = current;
            current = parent[current];
        }

        for (int j = count - 1; j >= 0; j--) {
            std::cout << (char)('a' + path[j]);
            if (j > 0) std::cout << " -> ";
        }
        std::cout << "\n";
    }
}

// Constructs the shortest path tree using an adjacency matrix
void dijkstra(double graph[V][V], int src) {
    double dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INFINITY;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        if (u == -1) break;

        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] > 0 && dist[u] != INFINITY
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent);
}

int main() {
    // Vertices: a=0, b=1, c=2, d=3, e=4
    double graph[V][V] = {
        { 0, 0, 0, 7, 0 }, // a
        { 3, 0, 4, 0, 0 }, // b
        { 0, 0, 0, 0, 6 }, // c
        { 0, 2, 5, 0, 0 }, // d
        { 0, 0, 0, 4, 0 }  // e
    };

    dijkstra(graph, 0);

    return 0;
}
