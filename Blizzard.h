#ifndef BLIZZARD_H
#define BLIZZARD_H
#include <string>
#include <iostream>
#include "Spell.h"

class Blizzard : public Spell {
 public:
  Blizzard(bool owner);
  ~Blizzard();

};

#endif
