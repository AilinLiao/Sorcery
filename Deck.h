#ifndef DECK_H
#define DECK_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Card.h"

class Deck {
  std::vector<Card *> deckCards;
  bool testing;
 public: 
  Deck(std::vector<Card *> deckCards, bool testing);
  std::vector<Card *>getCards();
  void attach(Card *c);
  void shuffle();
  Card *detach();
  ~Deck();
};

#endif

