#include "SudokuBoard.hpp"
#include <iostream>
#include "generator.cpp"

SudokuBoard::SudokuBoard() {
    for (auto& row : board)
        row.fill(0);
    for(auto& row : locked){
      for(auto& col : row){
        col = false;
      }
    }

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
    if (locked[row][col]) return false;

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
    if(!locked[row][col]){
      board[row][col] = num;
    }
}

int SudokuBoard::getCell(int row, int col) const {
    return board[row][col];
}
bool SudokuBoard::findEmptyCell(int &row, int &col) const {
  for( row = 0; row < 9; ++row)
    for( col = 0; col < 9; ++col)
      if (board[row][col] == 0) return true;
  return false;
}

bool SudokuBoard::isSafe(int row, int col,int num) const {
  return isValidMove(row, col, num);
}

bool SudokuBoard::solve() {
    int row, col;
    if (!findEmptyCell(row, col)) return true;

    std::vector<int> nums = {1,2,3,4,5,6,7,8,9};
    SimpleLCG rng(static_cast<unsigned long long>(time(nullptr)));
    shuffle(nums, rng);

    for (int num : nums) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;
            if (solve()) return true;
            board[row][col] = 0;  // backtrack
        }
    }

    return false;
}

void SudokuBoard::generateFullBoard() {
    board = {};
    solve();
}


void SudokuBoard::generatePuzzle(int visibleCells) {
    generateFullBoard();

    std::vector<std::pair<int, int>> positions;
    for (int row = 0; row < 9; ++row)
        for (int col = 0; col < 9; ++col)
            positions.emplace_back(row, col);

    SimpleLCG rng(static_cast<unsigned long long>(time(nullptr)));
    shuffle(positions, rng);

    int cellsToRemove = 81 - visibleCells;
    for (int i = 0; i < cellsToRemove; ++i) {
        int r = positions[i].first;
        int c = positions[i].second;
        board[r][c] = 0;
    }

    for (int row = 0; row < 9; ++row)
        for (int col = 0; col < 9; ++col)
            locked[row][col] = (board[row][col] != 0);
}
