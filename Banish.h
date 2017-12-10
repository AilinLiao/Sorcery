#ifndef BANISH_H
#define BANISH_H
#include <iostream>
#include <string>
#include "Spell.h"

class Banish : public Spell {
 public:
  Banish(bool owner);
  ~Banish();
};

#endif
