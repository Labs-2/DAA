#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;
int G[MAX][MAX];
int x[MAX];
int minColors = MAX;
int solutions[MAX][MAX];
int solCount = 0;

bool isSafe(int k, int c) {
    for (int j = 1; j <= n; j++) {
        if (G[k][j] && x[j] == c) {
            return false;
        }
    }
    return true;
}

void NextValue(int k) {
    do {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) return;
    } while (!isSafe(k, x[k]));
}

void mColoring(int k) {
    do {
        NextValue(k);
        if (x[k] == 0) return;
        if (k == n) {

            int colorSet[MAX] = {0};
            int usedColors = 0;
            for (int i = 1; i <= n; i++) {
                if (colorSet[x[i]] == 0) {
                    colorSet[x[i]] = 1;
                    usedColors++;
                }
            }
            for (int i = 1; i <= n; i++) {
                printf("%d ", x[i]);
            }
            printf("(Used Colors: %d)\n", usedColors);

            if (usedColors < minColors) {
                minColors = usedColors;
                solCount = 0;
            }
            if (usedColors == minColors) {
                for (int i = 1; i <= n; i++) {
                    solutions[solCount][i] = x[i];
                }
                solCount++;
            }
        } else {
            mColoring(k + 1);
        }
    } while (true);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of colors: ");
    scanf("%d", &m);

    printf("Enter adjacency matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) x[i] = 0;

    printf("\nAll Coloring Solutions:\n");
    mColoring(1);

    printf("\nMinimal Coloring Solutions (Using %d Colors):\n", minColors);
    for (int i = 0; i < solCount; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", solutions[i][j]);
        }
        printf("\n");
    }

    return 0;
}