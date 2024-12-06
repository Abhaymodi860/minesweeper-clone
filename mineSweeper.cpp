
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cell {
public:
    bool isMine;
    bool isRevealed;
    int adjacentMines;

    Cell() : isMine(false), isRevealed(false), adjacentMines(0) {}
};

class Board {
private:
    int size;
    vector<vector<Cell>> cells;

    void placeMines(int firstX, int firstY, int mineCount) {
        srand(time(0));
        int placedMines = 0;

        while (placedMines < mineCount) {
            int x = rand() % size;
            int y = rand() % size;

            // Ensure we don't place a mine on the first clicked cell
            if (!cells[x][y].isMine && (x != firstX || y != firstY)) {
                cells[x][y].isMine = true;
                placedMines++;
                updateAdjacentMines(x, y);
            }
        }
    }

    void updateAdjacentMines(int x, int y) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue; // Skip the cell itself
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
                    cells[newX][newY].adjacentMines++;
                }
            }
        }
    }

public:
    Board(int n) : size(n), cells(n, vector<Cell>(n)) {}

    void initialize(int firstX, int firstY, int mineCount) {
        placeMines(firstX, firstY, mineCount);
    }

    bool revealCell(int x, int y) {
        if (cells[x][y].isRevealed) return false; // Already revealed
        cells[x][y].isRevealed = true;
        return cells[x][y].isMine;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (cells[i][j].isRevealed) {
                    if (cells[i][j].isMine) {
                        cout << "* ";
                    }
                    else {
                        cout << cells[i][j].adjacentMines << " ";
                    }
                }
                else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    bool isGameWon() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!cells[i][j].isRevealed && !cells[i][j].isMine) {
                    return false; // Found a non-revealed safe cell
                }
            }
        }
        return true; // All safe cells revealed
    }
};

class Minesweeper {
private:
    Board board;
    int mineCount;

public:
    Minesweeper(int n, int mines) : board(n), mineCount(mines) {}

    void start() {
        int firstX, firstY;
        cout << "Enter the first cell to click (x y): ";
        cin >> firstX >> firstY;

        board.initialize(firstX, firstY, mineCount);
        bool gameOver = false;

        while (!gameOver) {
            board.display();
            int x, y;
            cout << "Enter the cell to reveal (x y): ";
            cin >> x >> y;

            if (board.revealCell(x, y)) {
                cout << "Game Over! You hit a mine!" << endl;
                gameOver = true;
            }
            else {
                if (board.isGameWon()) {
                    cout << "Congratulations! You've won!" << endl;
                    gameOver = true;
                }
            }
        }
    }
};

int main() {
    int n, mines;
    cout << "Enter the size of the board (n >= 9): ";
    cin >> n;
    cout << "Enter the number of mines: ";
    cin >> mines;

    if (n < 9 || mines < 1) {
        cout << "Invalid input. Size must be at least 9 and mines must be at least 1." << endl;
        return 1;
    }

    Minesweeper game(n, mines);
    game.start();
    return 0;
}
