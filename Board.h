#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "Minion.h"
#include "Ritual.h"
#include "ascii_graphics.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"

class Board{
  std::vector<Minion *> minions;
  Ritual *ritual;

 public:
  Board();
  ~Board();
  void attach(Minion *m);
  void detach(Minion *m);
  void setRitual(Ritual *r);
  Ritual *getRitual();
  void displayBoard();
  std::vector<Minion *> &getMinions();
};
#endif
