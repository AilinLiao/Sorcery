#include "EarthElemental.h"

EarthElemental::EarthElemental(bool owner)
  : Minion {"Earth Elemental", "", owner, 3, 4, 4} {}

EarthElemental::~EarthElemental(){
  for(int i = 0; i < enchants.size(); i++){
    delete enchants[i];
  }
}

