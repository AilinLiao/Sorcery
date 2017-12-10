#ifndef DARKRITUAL_H
#define DARKRITUAL_H
#include <iostream>
#include <string>
#include "Ritual.h"

class DarkRitual : public Ritual{
 public:
  DarkRitual(bool owner);
  ~DarkRitual();
};

#endif
