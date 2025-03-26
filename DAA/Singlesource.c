
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to print the shortest distances from the source
void printDistances(int dist[], int n) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX)
            printf("%d\t\tINF\n", i + 1); // Adjusting index for 1-based output
        else
            printf("%d\t\t%d\n", i + 1, dist[i]); // Adjusting index for 1-based output
    }
}

// Function to implement the Bellman-Ford algorithm
void bellmanFord(struct Edge edges[], int V, int E, int source) {
    int dist[V];

    // Step 1: Initialize distances from source to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[source] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printDistances(dist, V);
}

int main() {
    int V, E, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Edge edges[E];

    printf("Enter the edges in the format: source destination weight\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        edges[i].src = src - 1; // Adjusting for 0-based indexing
        edges[i].dest = dest - 1; // Adjusting for 0-based indexing
        edges[i].weight = weight;
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);
    source--; // Adjusting for 0-based indexing

    bellmanFord(edges, V, E, source);

    return 0;
}