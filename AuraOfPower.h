#ifndef AURAOFPOWER_H
#define AURAOFPOWER_H
#include <iostream>
#include <string>
#include "Ritual.h"

class AuraOfPower : public Ritual{  
 public:
  AuraOfPower(bool owner);
  ~AuraOfPower();
};

#endif
