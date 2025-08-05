#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "SudokuBoard.hpp"
#include "scoring.hpp"

class GameManager {
private:
    SudokuBoard board;
    Scoring scorer;

public:
    GameManager();
    void startGame();
    void play();
};

#endif
