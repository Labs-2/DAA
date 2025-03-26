#include <stdio.h>

struct Item {
    int profit;
    int weight;
    float ratio;
};

void GreedyKnapsack(int m, int n, struct Item items[]) {
    float x[n];
    int U = m;
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    for (int i = 0; i < n; i++) {

        if (items[i].weight <= U) {
            x[i] = 1.0;
            U -= items[i].weight;
        } else {

            x[i] = (float) U / items[i].weight;
            break;
        }
    }

    printf("Selected items (fractions):\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n", i + 1, x[i]);
    }
}

int main() {
    int m, n;

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &m);

    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter profit and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].profit, &items[i].weight);
        items[i].ratio = (float) items[i].profit / items[i].weight;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                struct Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    GreedyKnapsack(m, n, items);

    return 0;
}