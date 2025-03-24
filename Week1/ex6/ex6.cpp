#include <iostream>
#include <vector>
using namespace std;

bool isValid(int row, int col, vector<int>& board) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void printBoard(vector<int>& board) {
    int n = board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i] == j) {
				cout << "Q";
			}
            else {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void solve(int n, int row, vector<int>& board, int& count) {
    if (row == n) {
        count++;
        cout << count << ": " << endl;
        printBoard(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isValid(row, col, board)) {
            board[row] = col;
            solve(n, row + 1, board, count);
        }
    }
}

int main() {
    int n;
    cout << "Enter N: ";
    cin >> n;

    vector<int> board(n);
    int count = 0;

    solve(n, 0, board, count);

    if (count == 0) {
        cout << "No arrangement." << endl;
    }
    return 0;
}