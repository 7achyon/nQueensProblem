//N Queens Problem by 7achyon (MMXX)

#include <iostream>
#include <vector>
using namespace std;

//global variables
int N, checks, tries = 0;
vector<vector<int>> board;

//enums for the state of a space on the board
enum boardState {
    available = 0,
    occupied = 1,
    checking = 2
};

//initialise grid with dimensions provided by user
void init() {
    cout << "Enter the number of queens and length of the board: ";
    cin >> N;
    board.resize(N, vector<int>(N, available));
}

//draw grid to console
void draw() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            switch (board[y][x]) {
                case occupied:
                    cout << "Q";
                    break;
                case checking:
                    cout << ".";
                    break;
                default:
                    cout << "#";
            }
        }
        cout << "\n";
    }
}

//check if a queen would be safe on the current square
bool isSafe(int y, int x) {
    //since checks are done from top to bottom and left to right, it's unnecessary to check directly below and to the right of the space
    int i, j;

    //check upper
    for (int i = 0; i < y; i++) {
        if (board[i][x] != available) return false;
    }

    //check left
    for (int i = 0; i < x; i++) {
        if (board[y][i] != available) return false;
    }

    //check upper-right diagonal
    i = y - 1;
    j = x + 1;
    while (i >= 0 && j <= N) {
        if (board[i][j] != available) return false;
        i--;
        j++;
    }

    //check upper-left diagonal
    i = y - 1;
    j = x - 1;
    while (i >= 0 && j >= 0) {
        if (board[i][j] != available) return false;
        i--;
        j--;
    }
    return true;
}

//the recursive loop that attempts to solve the problem, using backtracking to brute force the solution
bool nQueensRecursion(int y) {
    //escape case
    if (y == N) return true;

    for (int j = 0; j < N; j++) {
        checks++;
        
        //output grid with current square being checked along with counter values for tracing the program's path
        board[y][j] = checking;
        draw();
        cout << "Checks: " << checks << "\n";
        cout << "Tries: " << tries << "\n";
        cout << "\n";
        board[y][j] = available;

        if(isSafe(y, j)) {
            //if the square is safe, place a queen
            tries++;
            board[y][j]  = occupied;

            //move to next row
            if (nQueensRecursion(y+1)) {
                return true;
            }
            
            //remove queen if row below has no valid squares
            board[y][j] = available;
        }
    }
    
    return false;
}

//entry point
int main() {
    init();
    nQueensRecursion(0);
    draw();
    cout << "\nSolved " << N << " Queen Problem in " << tries << " tries with " << checks << " checks.\n";
    return 0;
}
