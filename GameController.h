#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "Owner.h"

#include "ascii_graphics.h"
#include "Blizzard.h"
#include "Banish.h"
#include "AirElemental.h"
#include "FireElemental.h"
#include "ApprenticeSummoner.h"
#include "PotionSeller.h"
#include "EarthElemental.h"
#include "NovicePyromancer.h"
#include "MasterSummoner.h"
#include "CardFactory.h"

class GameController{

  Owner *o1;
  Owner *o2;

  //return types for getState()
  /*
  const int DRAW  = 0;
  const int ONE_WIN = 1;
  const int TWO_WIN = 2;
  const int IN_PROGRESS = 3;
  */
  bool testing = false;
  bool turn = true;
  int draw = 1;

 public:
  
  GameController(Owner *o1, Owner *o2, bool testing);
  /*
  //has a relatio test minions/enchants/spellsnship - don't forget to delete owner pointers in main.cc

  //getState() : produces an integer representing state of the game
  int getState();
  */
  //fetch(int j) : fetches minion i.
  Minion *fetch(Owner *o, int i);

  //fetch(Owner *o, int i); fetches card from Hand.
  Card *fetchHand(Owner *o, int i);

  //reset() : resets minions' hasAttacked to false
  void reset();
  
  void startGame(std::vector<std::string> fileargs);

 private:
  // GAME FLOW METHODS:
  void startGame_helper(std::string cmd);

  void displaySorcery();
    
  Owner *getAP();
  Owner *getNAP();
  
  // USE: the use command 
  void Use(int i, int p, int j);  // ADD BOOL OWNER LATER
  void Use(int i);

  // BOARD ADJUSTMENT METHODS:
  bool summon(int num, Minion *summoned);
  void bury(Minion *m);

  //Minion Enter play triggers:
  //-fire elemental: -1def to opp minion
  //-aura of power: +1/+1 to ur own minion (when you play)
  //-standstill: destroy any minion when it enters play

  //Start/end of turn triggers:
  //-potion seller: end of turn +1 def to all ur min
  //-dark ritual: start of turn +1 magic

  // TRIGGER METHODS
  void triggerPotionSeller();
  void triggerDarkRitual();

  void triggerFireElemental();
  void triggerAuraOfPower();
  bool triggerStandstill();
  
  // PLAY METHODS
  void playBlizzard();
  void playRecharge();
  void playRaiseDead();

  // ATTACK: the attack command
  void Attack(int i);
  void Attack(int i, int j);
  
  // PLAY: the play command
  void Play(int i);
  void Play(int i, int, std::string j);

  // UNSUMMON: when the spell unsummon is called.
  void unsummon(Minion *m, Owner *o);
  
};

#endif
