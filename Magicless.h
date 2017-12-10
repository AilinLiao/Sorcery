#ifndef MAGICLESS_
#define MAGICLESS_
#include <iostream>
#include <string>
#include <vector>
#include "Enchantment.h"

class Magicless : public Enchantment {
 public:
  Magicless(bool owner);
  ~Magicless();
};

#endif
