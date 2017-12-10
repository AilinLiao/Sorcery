#include "MasterSummoner.h"
using namespace std;
MasterSummoner::MasterSummoner(bool owner)
  :ActivatedAbilities{"Master Summoner", "Summon up to three 1/1 air elementals", owner, 3,2,3,2} {}

MasterSummoner::~MasterSummoner(){
  for(int i = 0; i < enchants.size(); i++){
    delete enchants[i];
  }
}
