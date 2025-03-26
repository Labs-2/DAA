
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to print the solution matrix
void printSolution(int **dist, int V) {
    printf("Shortest paths between all pairs of vertices:\n");
    printf(" \t"); // Header spacing
    for (int j = 0; j < V; j++) {
        printf("%d\t", j + 1); // Print column headers (vertex numbers)
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%d\t", i + 1); // Print row header (vertex number)
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement the Floyd-Warshall algorithm
void floydWarshall(struct Edge edges[], int V, int E) {
    // Dynamically allocate the distance matrix
    int **dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(V * sizeof(int));
    }

    // Initialize the distance matrix.  Crucially, initialize to infinity FIRST.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    // Set the distances for the existing edges.
    for (int i = 0; i < E; i++) {
        dist[edges[i].src][edges[i].dest] = edges[i].weight;
    }

    // Distance from a vertex to itself is always 0.
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }


    // Floyd-Warshall core logic
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative cycles (optional, but good practice)
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains negative weight cycle\n");
            // Free allocated memory before returning
            for (int i = 0; i < V; i++) {
                free(dist[i]);
            }
            free(dist);
            return;
        }
    }

    printSolution(dist, V);

    // Free the dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(dist[i]);
    }
    free(dist);
}

int main() {
    int V, E;

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

    floydWarshall(edges, V, E);

    return 0;
}