#include <stdio.h>

#define MAX_SIZE 100
int a[MAX_SIZE];

void MaxMin(int i, int j, int *max, int *min) {
    if (i == j) {

        *max = *min = a[i];
    } else if (i == j - 1) {

        if (a[i] < a[j]) {
            *max = a[j];
            *min = a[i];
        } else {
            *max = a[i];
            *min = a[j];
        }
    } else {

        int mid = (i + j) / 2;

        int max1, min1;
        MaxMin(i, mid, max, min);
        MaxMin(mid + 1, j, &max1, &min1);

        if (*max < max1) *max = max1;
        if (*min > min1) *min = min1;
    }
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max, min;

    MaxMin(0, n - 1, &max, &min);

    printf("Maximum value: %d\n", max);
    printf("Minimum value: %d\n", min);

    return 0;
}