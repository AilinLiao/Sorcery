#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include <vector>
#include <string>
#include <fstream>

#include "Card.h"

class CardFactory {
  std::string filename;
  bool turn;
 private:
  Card *makeCard(std::string n);
 public:
  CardFactory(std::string filename, bool turn);
  std::vector <Card *> makeDeck();
  ~CardFactory();
};

#endif
