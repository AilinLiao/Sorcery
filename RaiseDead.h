#ifndef RAISEDEAD_H
#define RAISEDEAD_H
#include <iostream>
#include <string>
#include "Spell.h"

class RaiseDead : public Spell{
  public:
    RaiseDead(bool owner);
    ~RaiseDead();
};

#endif
