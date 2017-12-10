#ifndef EARTHELEMENTAL_H
#define EARTHELEMENTAL_H
#include <vector>
#include <iostream>
#include <string>
#include "Minion.h"

class EarthElemental : public Minion{
 public:
  EarthElemental(bool owner);
  ~EarthElemental();
};

#endif
