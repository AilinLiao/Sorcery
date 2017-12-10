#include "AirElemental.h"

AirElemental::AirElemental(bool owner)
  : Minion{"Air Elemental", "", owner, 0, 1, 1} {}

AirElemental::~AirElemental(){
  for(int i = 0; i < enchants.size(); i++){
    delete enchants[i];
  }
}
