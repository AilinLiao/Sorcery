#include "CardFactory.h"
#include "AirElemental.h"
#include "EarthElemental.h"
#include "FireElemental.h"
#include "PotionSeller.h"
#include "NovicePyromancer.h"
#include "ApprenticeSummoner.h"
#include "MasterSummoner.h"
#include "Banish.h"
#include "Unsummon.h"
#include "Recharge.h"
#include "Disenchant.h"
#include "RaiseDead.h"
#include "Blizzard.h"
#include "GiantStrength.h"
#include "MagicFatigue.h"
#include "Silence.h"
#include "DarkRitual.h"
#include "AuraOfPower.h"
#include "StandStill.h"
#include "Magicless.h"
#include "HealthRestore.h"
#include "Steal.h"
#include "Guardian.h"

using namespace std;

CardFactory::CardFactory(string name, bool turn)
  : filename{name}, turn{turn}{}

Card *CardFactory::makeCard(string n){
  Card *c = nullptr;
  if (n == "Air Elemental") {
    c = new AirElemental(turn);
  } else if (n == "Earth Elemental") {
    c = new EarthElemental(turn);
  } else if (n == "Fire Elemental") {
    c = new FireElemental(turn);
  } else if (n == "Potion Seller") {
    c = new PotionSeller(turn);
  } else if (n == "Novice Pyromancer") {
    c = new NovicePyromancer(turn);
  } else if (n == "Apprentice Summoner") {
    c = new ApprenticeSummoner(turn);
  } else if (n == "Master Summoner") {
    c = new MasterSummoner(turn);
  } else if (n == "Banish") {
    c = new Banish(turn);
  } else if (n == "Unsummon") {
    c = new Unsummon(turn);
  } else if (n == "Recharge") {
    c = new Recharge(turn);
  } else if (n == "Disenchant") {
    c = new Disenchant(turn);
  } else if (n == "Raise Dead") {
    c = new RaiseDead(turn);
  } else if (n == "Blizzard") {
    c = new Blizzard(turn);
  } else if (n == "Giant Strength") {
    c = new GiantStrength(turn);
  } else if (n == "Magic Fatigue") {
    c = new MagicFatigue(turn);
  } else if (n == "Silence") {
    c = new Silence(turn);
  } else if (n == "Dark Ritual") {
    c = new DarkRitual(turn);
  } else if (n == "Aura of Power") {
    c = new AuraOfPower(turn);
  } else if (n == "Standstill") {
    c = new StandStill(turn);
  } else if (n == "Magicless") {
    c = new Magicless(turn);
  } else if (n == "Health Restore") {
    c = new HealthRestore(turn);
  } else if (n == "Steal") {
    c = new Steal(turn);
  } else if (n == "Guardian") {
    c = new Guardian(turn);
  }
  return c;
}

vector<Card *> CardFactory::makeDeck(){
  ifstream deckfile{filename};
  string cardName;
  vector<Card *> deck;
  while(getline(deckfile, cardName)){
    Card *c = makeCard(cardName);
    if(c == nullptr){ cout << "no such card " << cardName <<  endl;  continue;}
    deck.emplace_back(c);
  }
  return deck;
}

CardFactory::~CardFactory() {};
