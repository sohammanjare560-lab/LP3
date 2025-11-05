#include <iostream>
#include <vector>
using namespace std;

// Function to print the board
void printBoard(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    int i, j;

    // Check this column on upper side
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queens problem
bool solveNQueen(vector<vector<int>>& board, int row, int N) {
    // base case: all queens placed
    if (row >= N)
        return true;

    // Try placing queen in all columns one by one
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;  // place queen

            // recur to place rest
            if (solveNQueen(board, row + 1, N))
                return true;

            // if placing queen doesn't lead to a solution
            board[row][col] = 0; // BACKTRACK
        }
    }

    return false; // no column is safe in this row
}

int main() {
    int N;
    cout << "Enter the size of the board (N): ";
    cin >> N;

    // Create NxN board filled with 0
    vector<vector<int>> board(N, vector<int>(N, 0));

    // Place the first queen manually
    int firstRow, firstCol;
    cout << "Enter the position of the first Queen (row and column, 0-indexed): ";
    cin >> firstRow >> firstCol;

    // Check if position is valid
    if (firstRow < 0 || firstRow >= N || firstCol < 0 || firstCol >= N) {
        cout << "Invalid position!" << endl;
        return 0;
    }

    board[firstRow][firstCol] = 1; // place first queen

    // Start solving from the next row
    if (solveNQueen(board, firstRow + 1, N))
        printBoard(board, N);
    else
        cout << "No solution exists for given first queen position!" << endl;

    return 0;
}
