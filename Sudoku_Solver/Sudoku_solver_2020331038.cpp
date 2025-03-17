#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    bool emptySpot = false;

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                emptySpot = true;
                break;
            }
        }
        if (emptySpot) {
            break;
        }
    }

    if (!emptySpot) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != 8) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << "------+-------+------" << endl;
        }
    }
}


int main() {
    
     // Sample Sudoku puzzle (0 represents empty cells)
     
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    cout<< "Initial state of Sudoku board: \n";
    printBoard(board);
    cout<<'\n';
    if (solveSudoku(board)) {
        cout << "Solved Sudoku board: \n";
        printBoard(board);
    } else {
        cout << "No solution exists!";
    }

   
}
