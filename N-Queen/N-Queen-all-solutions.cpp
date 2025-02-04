#include <bits/stdc++.h>
using namespace std;

void printSolution(vector<vector<int>>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << "\n";
    }
    cout << "\n";
}

bool isSafe(vector<vector<int>>& board, int row, int col) {
    int n = board.size();

    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

void solveNQueen(vector<vector<int>>& board, int col, vector<vector<vector<int>>>& solutions) {
    int n = board.size();
    
    if (col >= n) {
        solutions.push_back(board);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            solveNQueen(board, col + 1, solutions);
            board[i][col] = 0;
        }
    }
}

void solveNQ(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<vector<int>>> solutions;

    solveNQueen(board, 0, solutions);

    cout << "Total Solutions: " << solutions.size() << "\n\n";
    for (auto& sol : solutions) {
        printSolution(sol);
    }
}

int main() {
    int n = 4;
    solveNQ(n);
    return 0;
}
