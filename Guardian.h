#ifndef GUARD_
#define GUARD_
#include <vector>
#include "TriggeredAbilities.h"

#include <string>

class Guardian : public TriggeredAbilities {
 public:
  Guardian(bool owner);
  ~Guardian();
};

#endif
