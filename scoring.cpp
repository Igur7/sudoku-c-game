#include "scoring.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

Scoring::Scoring() : points(0) {}

void Scoring::addPoints(int p) {
  points += p;
  if (points < 0) points = 0;
}

void Scoring::removePoints(int p) {
  points -= p;
  if (points < 0) points = 0;
}

int Scoring::getScore() {
  return points;
}

void Scoring::setScore(int p) {
  points = p;
}

void Scoring::saveScore(const std::string& playerName) {
  std::ifstream file("scores.txt");
  std::vector<std::pair<std::string, int>> scores;
  std::string name;
  int score;
  bool found = false;

  while (file >> name >> score) {
    if (name == playerName) {
      scores.emplace_back(name, points);
      found = true;
    } else {
      scores.emplace_back(name, score);
    }
  }
  file.close();

  if (!found) {
    scores.emplace_back(playerName, points);
  }

  std::ofstream outfile("scores.txt", std::ios::trunc);
  for (const auto& entry : scores) {
    outfile << entry.first << " " << entry.second << "\n";
  }
}


void Scoring::showScores() const {
  std::ifstream file("scores.txt");
  if (!file.is_open()) {
    std::cout << "Brak zapisanych wyników.\n";
    return;
  }

  std::vector<std::pair<std::string, int>> scores;
  std::string name;
  int score;
  while (file >> name >> score) {
    scores.emplace_back(name, score);
  }

  std::sort(scores.begin(), scores.end(),
            [](auto &a, auto &b) { return a.second > b.second; });

  std::cout << "\n--- Ranking ---\n";
  for (auto& entry : scores) {
    std::cout << entry.first << ": " << entry.second << "\n";
  }
}

void Scoring::reset() {
  points = 0;
}

bool Scoring::checkIfValidName(const std::string& playerName, const std::string& pw) {
  std::ifstream file("scores.txt");
  std::string name, storedPw;
  int score;
  while (file >> name >> storedPw >> score) {
    if (name == playerName) {
      return storedPw == pw;
    }
  }
  return false;
}

