#ifndef GRAVEYARD_H
#define GRAVEYARD_H
#include <vector>
#include <string>
#include <fstream>

#include "Minion.h"

class Graveyard {
  std::vector<Minion *> minions;
 public:
  void attach(Minion *);
  Minion *detach();
  std::vector<Minion *> &getMinions();
};

#endif
