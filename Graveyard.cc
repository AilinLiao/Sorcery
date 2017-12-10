#include "Graveyard.h"

using namespace std;

void Graveyard::attach(Minion *m) {
  minions.emplace_back(m);
}

Minion *Graveyard::detach() {
  Minion *m = minions[minions.size()-1];
  minions.pop_back();
  return m;
}

vector<Minion *> &Graveyard::getMinions(){
  return minions;
}
