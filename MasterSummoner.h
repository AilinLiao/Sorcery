#ifndef MASTERSUMMONER_H
#define MASTERSUMMONER_H
#include <iostream>
#include <string>
#include <vector>
#include "ActivatedAbilities.h"

class MasterSummoner : public ActivatedAbilities {
 public:
  MasterSummoner(bool owner);
  ~MasterSummoner();
};


#endif
