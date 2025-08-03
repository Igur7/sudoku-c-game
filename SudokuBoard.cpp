#include "SudokuBoard.hpp"
#include <iostream>

SudokuBoard::SudokuBoard() {
    for (auto& row : board)
        row.fill(0);
}

void SudokuBoard::generatePuzzle() {
    board[0][0] = 5;
    board[0][1] = 3;
    board[1][0] = 6;
    board[4][4] = 7;
    board[8][8] = 9;
}

void SudokuBoard::display() const {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0)
            std::cout << "------+-------+------\n";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0)
                std::cout << "| ";
            std::cout << (board[i][j] ? std::to_string(board[i][j]) : ".") << " ";
        }
        std::cout << "\n";
    }
}

bool SudokuBoard::isValidMove(int row, int col, int num) const {
    if (board[row][col] != 0) return false;

    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = row / 3 * 3, startCol = col / 3 * 3;
    for (int i = startRow; i < startRow + 3; ++i)
        for (int j = startCol; j < startCol + 3; ++j)
            if (board[i][j] == num)
                return false;

    return true;
}

void SudokuBoard::setCell(int row, int col, int num) {
    board[row][col] = num;
}

int SudokuBoard::getCell(int row, int col) const {
    return board[row][col];
}
