#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP
#include <array>

class SudokuBoard {
private:
  std::array<std::array<int, 9>, 9> board;

public:
  SudokuBoard();
  void generatePuzzle();
  void display() const;
  bool isValidMove(int row, int col, int num) const;
  void setCell(int row, int col, int num);
  int getCell(int row, int col) const;
};

#endif //SUDOKUBOARD_HPP
