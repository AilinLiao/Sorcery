#ifndef HAND_H
#define HAND_H
#include <string>
#include <vector>

#include "Card.h"
#include "Deck.h"

class Hand {
  const int maxNumCards = 5; 
  std::vector<Card *> cards;
  Deck deck;
 public:
  void draw ();
  Card *play (int i);
};

#endif

