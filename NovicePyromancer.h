#ifndef NOVICEPYROMANCER_H
#define NOVICEPYROMANCER_H
#include <iostream>
#include <vector>
#include <string>
#include "ActivatedAbilities.h"

class NovicePyromancer : public ActivatedAbilities {
 public:
  NovicePyromancer(bool owner);
  ~NovicePyromancer();
};

#endif
