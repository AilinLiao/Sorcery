#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Minion.h"

class Board{
  std::vector<Minion*> minions;
  //  vector<Spell *> spells;
  //Ritual * ritual;

 public:
  void attach(Minion *m);
  void detach(Minion *m);
  std::vector<Minion *> &getMinions();

};
#endif
