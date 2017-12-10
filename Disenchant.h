#ifndef DISENCHANT_H
#define DISENCHANT_H
#include <string>
#include <iostream>
#include "Spell.h"

class Disenchant : public Spell {
public:
  Disenchant(bool owner);
  ~Disenchant();
};

#endif
