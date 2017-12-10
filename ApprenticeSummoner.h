#ifndef APPSUM_H
#define APPSUM_H
#include <vector>
#include <string>
#include "ActivatedAbilities.h"

class ApprenticeSummoner : public ActivatedAbilities {
 public:
  ApprenticeSummoner(bool owner);
  ~ApprenticeSummoner();
};

#endif

