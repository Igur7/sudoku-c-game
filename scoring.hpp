#ifndef SCORING_HPP
#define SCORING_HPP

#include <iostream>
#include <string>

const int POINTS_CORRECT = 10;
const int POINTS_WRONG = 5;
const int POINTS_BONUS = 50;

class Scoring {
private:
  int points;
  std::string name;
  std::string password;
public:
  Scoring();
  void addPoints(int point);
  void removePoints(int point);
  int getScore();
  void setScore(int point);

  void saveScore(const std::string& playerName);
  void showScores() const;
  void reset();
  std::string getName(){ return name; }
  void setName(const std::string& playerName){ name = playerName; }
  bool checkIfValidName(const std::string& playerName,const std::string& pw);
};

#endif
