#include "GameManager.hpp"
#include <iostream>

GameManager::GameManager() {}

void GameManager::startGame() {
    int level;
    int visibleCells = 0;
    std::string playerName;

    std::cout << "Podaj swoje imię: ";
    std::cin >> playerName;
    scorer.setName(playerName);

    do {
        std::cout << "Wybierz poziom trudności:\n"
                  << "1 - łatwy (55 widocznych pól)\n"
                  << "2 - średni (45 widocznych pól)\n"
                  << "3 - trudny (35 widocznych pól)\n"
                  << "0 - pokaż ranking\n";
        std::cin >> level;

        if (level == 0) {
            scorer.showScores();
        }
    } while (level == 0 || level < 1 || level > 3);

    switch (level) {
        case 1:
            visibleCells = 55;
        break;
        case 2:
            visibleCells = 45;
        break;
        case 3:
            visibleCells = 35;
        break;
    }

    board.generatePuzzle(visibleCells);
    scorer.reset();
}

void GameManager::play() {
    while (true) {
        board.display();
        std::cout << "Punkty: " << scorer.getScore() << "\n";

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
            scorer.addPoints(10);
        } else {
            std::cout << "Nieprawidłowy ruch!\n";
            scorer.removePoints(5);
        }
    }

    std::cout << "Gra zakończona. Twój wynik: " << scorer.getScore() << "\n";
    scorer.saveScore(scorer.getName());
}
