#include <stdio.h>
#include <stdlib.h>

// Print the board (for visualization)
void print_board(int** board, int n, int* solution_count) {
    printf("\nSolution %d:\n", *solution_count);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

// Check if placing a queen at (row, col) is safe
int is_safe(int row, int col, int** board, int n) {
    // Check column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return 0;
        }
    }
    
    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return 0;
        }
    }
    
    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return 0;
        }
    }
    
    return 1;
}


// Backtracking function
void backtrack(int row, int** board, int n, int* solution_count) {
    if (row == n) { // Base case: all queens placed
        (*solution_count)++;
        print_board(board, n, solution_count);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (is_safe(row, col, board, n)) {
            board[row][col] = 1; // Place queen
            backtrack(row + 1, board, n, solution_count); // Recurse
            board[row][col] = 0; // Backtrack: remove queen
        }
    }
}

// Main function to initialize and start solving
void solve_n_queens(int n) {
    // Dynamically allocate 2D board
    int** board = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        board[i] = (int*)calloc(n, sizeof(int)); // Initialize with zeros
    }
    
    int solution_count = 0;
    backtrack(0, board, n, &solution_count);
    
    printf("Total solutions: %d\n", solution_count);
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

// Example usage
int main(int ac, char **av) {
    int n = atoi(av[1]); // Example for 4x4 board
    solve_n_queens(n);
    return 0;
}