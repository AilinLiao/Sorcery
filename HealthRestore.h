#ifndef HEALTH_
#define HEALTH_
#include <iostream>
#include <string>
#include "Ritual.h"

class HealthRestore : public Ritual{  
 public:
  HealthRestore(bool owner);
  ~HealthRestore();
};

#endif
