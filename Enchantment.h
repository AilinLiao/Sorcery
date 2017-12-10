#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <iostream>
#include <string>
#include "Card.h"

class Enchantment : public Card {
  
 protected:
  Enchantment(std::string name, std::string descript, bool owner, int origCost);
 public:
  virtual ~Enchantment();
};

#endif
