#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H
#include <iostream>
#include <string>
#include "Enchantment.h"

class MagicFatigue : public Enchantment {
 public:
  MagicFatigue(bool owner);
  ~MagicFatigue();
};

#endif
