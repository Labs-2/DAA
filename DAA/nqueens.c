#include <stdio.h>
#include <stdlib.h>  // For abs() function

int board[20], solutionCount = 0;

int canPlace(int row, int col) {
    for (int i = 1; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
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
            if (row == n) 
                printSolution(n);
            else 
                nQueens(row + 1, n);
        }
    }
}

int main() {
    int n;
    printf("Enter number of queens: ");
    scanf("%d", &n);

    if (n < 1 || n > 20) {
        printf("Invalid input. Please enter a value between 1 and 20.\n");
        return 1;
    }

    nQueens(1, n);

    if (solutionCount == 0) {
        printf("\nNo solutions found for %d-Queens.\n", n);
    }

    return 0;
}
