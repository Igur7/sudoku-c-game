#include "SudokuBoard.hpp"
#include <iostream>

int main() {
    SudokuBoard board;
    board.generateFullBoard();
    int visablecells;
    std::cout<<"Wprowadz ilosc widocznych pol: "<<std::endl;
    std::cin>>visablecells;
    board.generatePuzzle(visablecells);

    while (true) {
        board.display();
        int row, col, num;
        std::cout << "Wprowadź wiersz (0-8), kolumnę (0-8) i liczbę (1-9), lub -1 by wyjść: ";
        std::cin >> row;
        if (row == -1) break;
        std::cin >> col >> num;

        if (row < 0 || row > 8 || col < 0 || col > 8 || num < 1 || num > 9) {
            std::cout << "Nieprawidłowe dane.\n";
            continue;
        }

        if (board.isValidMove(row, col, num)) {
            board.setCell(row, col, num);
        } else {
            std::cout << "Nieprawidłowy ruch!\n";
        }
    }

    std::cout << "Koniec gry.\n";
    return 0;
}
