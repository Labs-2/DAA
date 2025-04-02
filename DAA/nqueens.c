​
22BQ1A05F1NARRAVULA VISHNU PRIYA
​
#include <stdio.h>
#include <math.h>

int board[20], solutionCount = 0;

int canPlace(int row, int col) {
    for (int i = 1; i < row; i++) {
        if (board[i] == col || fabs(board[i] - col) == fabs(i - row))
            return 0;
    }
    return 1;
}

void printSolution(int n) {
    printf("\nSolution %d:\n", ++solutionCount);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i] == j) printf("Q ");
            else printf("- ");
        }
        printf("\n");
    }
}

void nQueens(int row, int n) {
    for (int col = 1; col <= n; col++) {
        if (canPlace(row, col)) {
            board[row] = col;
            if (row == n) printSolution(n);
            else nQueens(row + 1, n);
        }
    }
}

void main() {
    int n;
    printf("Enter number of queens : ");
    scanf("%d", &n);
    nQueens(1, n);
    if (solutionCount == 0) {
        printf("\nNo solutions found for %d-Queens.\n", n);
    }
}