#include "Hand.h"

using namespace std;


Hand::Hand ()
  : maxNumCards{maxNumCards}, numCards{numCards}, cards{cards}, deck{deck} {}

//Draws the first card in deck to hand. increment numCards if not at maxNumCards.
void Hand::draw () {
  if (numCards != maxNumCards && deck.deckCards.begin()) {
    card.emplace_back(deck.deckCards.begin());
    deck.deckCards.erase(deck.deckCards.begin());
  } else if (!deck.deckCards.begin()) {
    //game over for player who's bool turn is currently true.
  } else {
    continue; // at maxNumCards allowed for deck.
  }
}

// Returns a Card pointer at index i of the cards vector
Card *Hand::play (int i) { return card[i]; }

