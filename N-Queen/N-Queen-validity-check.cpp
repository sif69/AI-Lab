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
        if (board[row][i]) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j]) return false;

    return true;
}


bool solveNQueen(vector<vector<int>>& board, int col) {
    int n = board.size();
    if (col >= n) return true;

    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueen(board, col + 1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}


bool isValidBoard(vector<vector<int>>& board) {
    int n = board.size();
    vector<int> rows(n, -1);

    for (int col = 0; col < n; col++) {
        bool found = false;
        for (int row = 0; row < n; row++) {
            if (board[row][col] == 1) {
                if (rows[row] != -1 || !isSafe(board, row, col))
                    return false; 
                rows[row] = col;
                found = true;
                break;
            }
        }
        if (!found) return false; 
    }
    return true;
}


void solveBoard(vector<vector<int>>& board) {
    if (isValidBoard(board)) {
        cout << "The given board is already a valid solution:\n";
        printSolution(board);
        return;
    }

    cout << "Invalid board! Finding a valid solution...\n";
    int n = board.size();
    vector<vector<int>> newBoard(n, vector<int>(n, 0));

    if (solveNQueen(newBoard, 0))
        printSolution(newBoard);
    else
        cout << "No valid arrangement exists!\n";
}

int main() {
    int n;
    cout << "Enter board size (n): ";
    cin >> n;
    
    vector<vector<int>> board(n, vector<int>(n, 0));
    cout << "Enter the board (use Q for queen and . for empty cell):\n";
    
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++)
            board[i][j] = (row[j] == 'Q' ? 1 : 0);
    }

    solveBoard(board);
    return 0;
}
