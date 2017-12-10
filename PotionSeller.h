#ifndef POTIONSELLER_H
#define POTIONSELLER_H
#include <iostream>
#include <string>
#include <vector>
#include "TriggeredAbilities.h"

class PotionSeller : public TriggeredAbilities {
 public:
  PotionSeller(bool owner);
  ~PotionSeller();
};

#endif

