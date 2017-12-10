#ifndef FIREELEMENTAL_H
#define FIREELEMENTAL_H
#include <iostream>
#include <vector>
#include <string>
#include "TriggeredAbilities.h"

class FireElemental : public TriggeredAbilities {
 public:
  FireElemental(bool owner);
  ~FireElemental();
};

#endif

