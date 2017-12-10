#include "GameController.h"
#include "Card.h"
using namespace std;

// CONSTRUCTOR //
GameController::GameController(Owner *o1, Owner *o2, bool testing)
  : o1{o1}, o2{o2}, testing{testing}{}

/*
  ===============================================
  USEFUL GAMECTRLER METHODS
  ===============================================
*/


Minion *GameController::fetch(Owner *o, int i) {
  if (i >= o->getBoard().getMinions().size() || i < 0) {
    cerr << "Cannot fetch minion. Please enter valid index" << endl;
    return nullptr;
  }
  return o->getBoard().getMinions()[i];
}

Card *GameController::fetchHand(Owner *o, int i) {
  vector <Card *> cv = o->getHand().getCards();
  if (i >= cv.size() || i < 0) {
    cerr << "Cannot fetch card. Please enter valid index" << endl;
    return nullptr;
  }
  return o->getHand().getCards()[i];
}

//reset() : resets minions' hasAttacked to false
void GameController::reset() {
  for (int i = 0; i < getAP()->getBoard().getMinions().size(); i++) {
    getAP()->getBoard().getMinions()[i]->attacked(true);
  }
}

void GameController::bury(Minion *m) {//Will implement for player two later
  Owner *o = m->getOwner() ? o1 : o2;
  o->getGraveyard().attach(m);
  o->getBoard().detach(m);
  int i = o1->getGraveyard().getMinions().size();
  cout << i << " minions have died" << endl;
  int j = o1->getBoard().getMinions().size();
  cout << j << " minions are on board" << endl;
  Ritual *r = o->getBoard().getRitual();
  if(!r) return;
  if(r->getName() == "Health Restore"){
    if(r->getCurrCharge() < r->getCurrActCost()) return;
    r->charge(-1);
    o->addHealth(1);
  }
}


Owner *GameController::getAP() {
  if (turn) return o1;
  return o2;
}

Owner *GameController::getNAP() {
  if (turn) return o2;
  return o1;
}


bool GameController::summon(int num, Minion *summoned) {
  Board &b = getAP()->getBoard();
  int res = (5 - b.getMinions().size()) < num ? (5 - b.getMinions().size()) : num;
  if (res == 0) return false;
  b.attach(summoned);
  for (int i = 0; i < res-1; ++i) {
    AirElemental *a = new AirElemental(turn);
    b.attach(a);
  }
  return true;
}

void GameController::unsummon(Minion *m, Owner *o) {
  o->getBoard().detach(m);
  o->getDeck().attach(m);
}

void GameController::triggerPotionSeller(){
  bool exists = false;
  vector<Minion *> cards = getAP()->getBoard().getMinions();
  int size = cards.size();
  for(int i = 0; i < size; i++) {
    if(cards[i]->getName() == "Potion Seller"){
      exists = true;
      break;
    }
  }
  if(exists){
    for(int i = 0; i < size; i++){
      cards[i]->addCurrDef(1);
    }
  }
}

void GameController::triggerDarkRitual(){
  Ritual *r = getAP()->getBoard().getRitual();
  if (!r) return;
  if (r->getCurrCharge() <= 0) return;
  if (r && r->getName() == "Dark Ritual") {
    getAP()->addMagic(1);
    // add decrease in charge
    r->charge(-1);
  }
}

void GameController::displaySorcery() {
  for(int i = 0; i < CENTRE_GRAPHIC.size(); i++){
    cout << CENTRE_GRAPHIC[i] << endl;
  }
}

/*
  ========================================
  GAME LOOP STARTS
  ========================================
*/


void GameController::startGame(vector<string> fileargs) {

  string name1, name2;
   //LOAD HAND FOR BOTH PLAYERS
  for (int i = 0; i < 4; i++) {
    getAP()->draw();
    getNAP()->draw();
  }
  //INITIALIZING FROM FILE//
  int size = fileargs.size();
  for (int i = 0; i < size; ++i) {
    startGame_helper(fileargs[i]);
    if(draw == 0){ cout << "GAME OVER" << endl; return; }
  }
  //GET PLAYERS NAMES//
  if (o1->getName() == "") {
    cout << "What is the first player's name?" <<endl;
    cin >> name1;
    cout << "player1's name is " << name1 << endl;
    o1->setName(name1);
  }
  if (o2->getName() == "") {
    cout << "What is the second player's name?" <<endl;
    cin >> name2;
    cout << "player2's name is " << name2 << endl;
    o2->setName(name2);
  }
 
  //STARTS GAME
  string cmd;
  while(getline(cin, cmd)){
    startGame_helper(cmd);
    if(draw == 0) break;
  }
  //ENDS GAME
  cout << "GAME OVER" << endl;
}

void GameController::startGame_helper(string cmd) {
  istringstream iss{cmd};
  string currcmd;
  while(iss >> currcmd){
    
    //Player has died
    if(getNAP()->getHealth() <= 0){
      cout << getAP()->getName() << " has won! " << endl;
      draw = 0;
      break;
    }
    
    if (currcmd == "help") {
      cout << "HELP" << endl; //will insert help method later
    } else if (currcmd == "end") {
      triggerPotionSeller();
      reset();
      turn = !turn;
      triggerDarkRitual();
      getAP()->draw();
      getAP()->addMagic(1);
      
       //display board
      o1->displayOwner(1);
      o1->getBoard().displayBoard();
      displaySorcery();
      o2->getBoard().displayBoard();
      o2->displayOwner(2);
      //
      
      cout << "It is " << getAP()->getName() << "'s turn now." << endl;
      cout << currcmd << endl;
    } else if (currcmd == "quit") {
      draw = 0;
      break;
    } else if (currcmd == "draw") {
      if (!testing) continue;
      getAP()->draw();
    } else if (currcmd == "discard") {
      cout << currcmd << endl;
      if (!testing) continue;
      int cardNum = -1;
      iss >> cardNum;
      if(iss.fail()){
	cerr << "Please enter a valid index" << endl;
	continue;
      }
      Card *c = getAP()->getHand().detach(cardNum);
      delete c;
    } else if (currcmd == "attack") {
      cout << currcmd << endl;
      int arg1, arg2 = -1;
      iss >> arg1;
      if(iss.fail()){
	cerr << "Please enter a valid index" << endl;
	continue;
      }
      iss >> arg2;
      if(iss.fail()){
	Attack(arg1);
      }else{
	Attack(arg1, arg2);
      }
      cout << "argument 1 is " << arg1 << " and argument 2 is " << arg2 << endl;
    } else if (currcmd == "play") {
      cout << currcmd << endl;
      int arg1, arg2;
      string arg3;
      iss >> arg1;
      cout << "arg1 is" <<  arg1 << endl;
      if(iss.fail()) {
	cerr << "Please enter valid command argument " << endl;
	continue;
      }
      iss >> arg2; iss >> arg3;
      if(iss.fail()) {
	Play(arg1);
      }else{
	Play(arg1, arg2, arg3);
      }
    } else if (currcmd == "use") {
      cout << currcmd << endl;
      int  arg1, arg2, arg3 = -1;
      iss >> arg1;
      if (iss.fail()) {
	cerr << "Please enter valid command argument " << endl;
	continue;
      }
      iss >> arg2; iss >> arg3;
      if (iss.fail()){
	cout << "arg1 is " <<  arg1 << endl; 
	Use(arg1);
      } else {
	Use(arg1, arg2, arg3);
	cout << "arg1 is " << arg1 << " arg2 is " << arg2 << " arg3 is " << arg3 << endl;
      }
    } else if (currcmd == "inspect") {
      cout << currcmd << endl;
      int arg;
      iss >> arg;
      if (iss.fail()){ cout << "Please enter valid command" << endl; continue;}
      --arg;
      vector <Minion *> minions = getAP()->getBoard().getMinions();

      //ERROR CHECKING
      if(arg < 0 || arg >= minions.size() ){
	cout << "Please enter a valid index to inspect minion" << endl;
      }
      //
      
      getAP()->getBoard().getMinions()[arg]->displayMinion();
    } else if (currcmd == "hand") {
      int s = getAP()->getHand().getCards().size();
      for (int i = 0; i < s; i++) {
	cout << "Card " << i << " is " << getAP()->getHand().getCards()[i]->getName() << endl;
      }
      cout << "MAGIC COUNT: " << getAP()->getMagic() << endl;
      cout << "Health Count: " << getAP()->getHealth() << endl;
      cout << currcmd << endl;
      getAP()->getHand().displayHand();
    } else if (currcmd == "board") {
      //display board
      o1->displayOwner(1);
      o1->getBoard().displayBoard();
      displaySorcery();
      o2->getBoard().displayBoard();
      o2->displayOwner(2);
      int s = getAP()->getBoard().getMinions().size();
      for (int i = 0; i < s; i++) {
	cout << "Minion " << i << " is " << getAP()->getBoard().getMinions()[i]->getName() << endl;
      }
      cout << currcmd << endl;
    }
  }
}


/*
  =========================================
  USE COMMAND
  =========================================
*/

// For Minions with abilities only. 
void GameController::Use(int i, int p, int j) {
  --i;
  --j;
  Owner  *o = nullptr;

  // ERROR CHECKING
  if(p == 1) o = o1;
  else if(p == 2) o = o2;
  else {
    cout << "Invalid Player index entered." << endl;
    return;
  }

  vector <Minion *> board1 = getAP()->getBoard().getMinions();
  vector <Minion *> board2 = o->getBoard().getMinions();
  if(i < 0 || i >= board1.size() || j < 0 || j >= board2.size()){
    cout << "Invalid mininon selected." << endl;
    return;
  }
  //
  
  Minion *m1 = fetch(getAP(), i);
  if(m1->getMagicless() > 0){
    cout << "Cannot use ability on a minion." << endl;
    return;
  }
  
  ActivatedAbilities *a = dynamic_cast<ActivatedAbilities *>(m1);
  if(!a){cout <<  "Minion " << m1->getName() << " has no activated abilities." << endl; }
  int amt = 0;
  int difference = getAP()->getMagic()-a->getOrigCost();
  if (!testing){
    if(difference < 0) return;
    amt = -a->getOrigCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*a->getOrigCost();
  }
  if (a->getHasAttacked()) return;
  Minion *m2 = fetch(o, j);
  
  if(a->getName() != "Novice Pyromancer"){
    cerr << "Cannot use " << a->getName() << " on " << m2->getName() << "."  << endl;
    return;
  }
  bool alive = m2->receiveAttackFrom(a, true);
  getAP()->addMagic(amt);
  a->attacked();
  if(!alive){
    bury(m2);
  }
}


void GameController::Use(int i) {
  --i;
  
  // ERROR CHECKING
  vector <Minion *> board1 = getAP()->getBoard().getMinions();
  if(i < 0 || i >= board1.size()){
    cout << "Invalid mininon selected." << endl;
    return;
  }
  //
  
  Minion *m = fetch(getAP(), i);
  ActivatedAbilities *a = dynamic_cast<ActivatedAbilities *>(m);

  if(m->getMagicless() > 0){
    m->attacked();
    getNAP()->addMagic(-1);
    return;
  }
  
  if(!a){cout <<  "Minion " << m->getName() << " has no activated abilities." << endl; return; }
  int amt = 0;
  int difference = getAP()->getMagic()-a->getCurrActCost();
  if (!testing){
    if(difference < 0) return;
    amt = -a->getCurrActCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*a->getCurrActCost();
  }
  cout << "Name is " << m->getName() << endl;
  if (m->getHasAttacked()) return;
  if ((m->getName() != "Apprentice Summoner") && (m->getName() != "Master Summoner")){
    cerr << "Invalid Card" << endl;
    return;
  }
  int num =  m->getName() == "Master Summoner" ? 3 : 1;
  getAP()->addMagic(amt);
  AirElemental *air = new AirElemental(turn);
  bool res = summon(num, air);
  if(res){
    m->attacked();
  }
}


void GameController::triggerFireElemental() {
  bool exists = false;
  vector <Minion *> cards1 = getNAP()->getBoard().getMinions();
  vector <Minion *> cards2 = getAP()->getBoard().getMinions();
  int size = cards1.size();
  for (int i = 0; i < size; i++) {
    if (cards1[i]->getName() == "Fire Elemental") {
      exists = true;
      break;
    }
  }
  if (exists) {
    cards2[cards2.size()-1]->addCurrDef(-1);
    if (cards2[cards2.size()-1]->getCurrDef() <= 0) {
      bury(cards2[cards2.size()-1]);
    }
  }  
}

void GameController::triggerAuraOfPower() {
  Ritual *r = getAP()->getBoard().getRitual();
  if(!r) return;
  if (r->getCurrCharge() <= 0) return;
  if (r && r->getName() == "Aura Of Power") {
    vector <Minion *> c = getAP()->getBoard().getMinions();
    c[c.size()-1]->addCurrDef(1);
    c[c.size()-1]->addCurrAttack(1);
    r->charge(-1);
  }
}

bool GameController::triggerStandstill() {
  Ritual *r1 = getAP()->getBoard().getRitual();
  Ritual *r2 = getNAP()->getBoard().getRitual();
  vector <Minion *> minions = getAP()->getBoard().getMinions();
  Minion *m = minions[minions.size()-1];
  if (r1 && r1->getName() == "Standstill"){
    if(r1->getCurrCharge() < 2) return false;
    bury(m);
    r1->charge(-2);
    return true;
  }
  if (r2 && r2->getName() == "Standstill"){
    if(r2->getCurrCharge() < 2) return false;
    bury(m);
    r2->charge(-2);
    return true;
  }
  return false;
}

/*
  ==========================================
  PLAY COMMANDS
  ==========================================
*/

void GameController::playBlizzard() {
  int size1 = getAP()->getBoard().getMinions().size();
  int size2 = getNAP()->getBoard().getMinions().size();
  Blizzard *b = new Blizzard(true);
  for (int i = 0; i < size1; i++) {
    fetch(getAP(),i)->receiveAttackFrom(*b);
  }
  for (int i = 0; i < size2; i++) {
    fetch(getNAP(),i)->receiveAttackFrom(*b);
  }
  delete b;
}

void GameController::playRecharge() {
  getAP()->getBoard().getRitual()->charge(3);
}

void GameController::playRaiseDead() {
  Minion *m = getAP()->getGraveyard().detach();
  getAP()->getBoard().attach(m);
}


void GameController::Play(int i) {
  --i;
  int size = getAP()->getHand().getCards().size();
  
  //ERROR CHECKING
  if (i >= size || i < 0) {
    cout << "Invalid index chosen. Please play again." << endl;
    return;
  }
  //
  
  Card *c = fetchHand(getAP(), i);
  cout << "Card Name is " << c->getName() << endl;
  cout << "CARD TYPE: " << c->getType() << endl;
  int amt = 0;
  int difference = getAP()->getMagic()-c->getOrigCost();
  if (!testing){
    if(difference < 0) return;
    amt = -c->getOrigCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c->getOrigCost();
  }
  if (c->getType() == "Spell") {
    string name = c->getName();
    if (name == "Recharge" && getAP()->getBoard().getRitual()){
      playRecharge();
      Card *spell = getAP()->getHand().detach(i);
      delete spell;
    } else if (name == "Raise Dead" && getAP()->getGraveyard().getMinions().size() > 0){
      playRaiseDead();
      Card *spell = getAP()->getHand().detach(i);
      delete spell;
    }else if (name == "Blizzard"){
      playBlizzard();
      Card *spell = getAP()->getHand().detach(i);
      delete spell;
    }else if (name == "Steal"){
      int size = getNAP()->getHand().getCards().size();
      if (size <= 0) return;
      Card *spell = getAP()->getHand().detach(i);
      delete spell;
      int stolenCardIndex = rand()%size;
      Card *stolen =  getNAP()->getHand().detach(stolenCardIndex);
      stolen->toggleOwner();
      getAP()->getHand().attach(stolen);
    }else cout << "Cannot play card.!" << endl;
  }else if (c->getType() == "Minion"){
    int size = getAP()->getBoard().getMinions().size();
    if(size >= 5){cout << "Board is Full" << endl; return;}
    Card *m = getAP()->getHand().detach(i);
    Minion *min = dynamic_cast<Minion *>(m);
    getAP()->getBoard().attach(min);
    triggerAuraOfPower();
    bool triggered = triggerStandstill();
    if(!triggered) triggerFireElemental();
  }else if (c->getType() == "Ritual"){
    Ritual *r = dynamic_cast<Ritual *>(c);
    getAP()->getBoard().setRitual(r); //sets/replaces Ritual on Board
    getAP()->getHand().detach(i);
  }else{
    cout << "Cannot play card." << endl;
  }
  getAP()->addMagic(amt);
}


void GameController::Play(int i, int p, string j) {
  --i;
  int size = getAP()->getHand().getCards().size();
  if (i >= size || i < 0) {
    cout << "Invalid index chosen, cannot play card. Please play again." << endl;
    return;
  }
  Card *c1 = fetchHand(getAP(), i);
  Owner *o = p == 1 ? o1 : o2;
  int num;
  istringstream iss{j};
  // J is a ritual
  if((j == "r") && c1->getName() == "Recharge") {
    Ritual *r = o->getBoard().getRitual();
    if(!r) return;
    int amt = 0;
    if(!testing){
      if(getAP()->getMagic() < c1->getOrigCost()) return;
      amt = -1*c1->getOrigCost();
    }else{
      int difference = getAP()->getMagic()-c1->getOrigCost();
      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
    }
    r->charge(3);
    getAP()->addMagic(-1*c1->getOrigCost());
  }else if((j == "r") && c1->getName() == "Banish") {
    Ritual *r = o->getBoard().getRitual();
    if(!r) return;
    o->getBoard().setRitual(nullptr);
  }else if (iss >> num){
    --num;
    int size = o->getBoard().getMinions().size();
    if (num >= size || num < 0) {
      cout << "Invalid index chosen, cannot play card. Please play again." << endl;
      return;
    }
    Minion *m = fetch(o, num);
    if(c1->getType() == "Enchantment"){
      int amt = 0;
      if (!testing) {	
	if(getAP()->getMagic() < c1->getOrigCost()) return;
	amt = -1*c1->getOrigCost();
      }else{
        int difference = getAP()->getMagic()-c1->getOrigCost();
        amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
      }
      ActivatedAbilities *a = dynamic_cast<ActivatedAbilities *>(m);
      Enchantment *e = dynamic_cast<Enchantment *>(c1);
      if(!a){
	m->receiveEnchantFrom(e);
      }else{
	a->receiveEnchantFrom(e);
      }
      if(c1->getName() == "Magicless"){
	m->addMagicless(1);
      }
      getAP()->addMagic(amt);
      getAP()->getHand().detach(i);
    }else if(c1->getType() == "Spell"){
	  if(c1->getName() == "Unsummon") {
	    int amt = 0;
	    if (!testing) {
	      if(getAP()->getMagic() < 1) return;
	      amt = -1*c1->getOrigCost();
	    }
	    else {
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    unsummon(m,o);
	    getAP()->addMagic(amt);
	    getAP()->getHand().detach(i);
	  }else if(c1->getName() == "Banish") {
	    int amt = 0;
	    if (!testing) {
	      if(getAP()->getMagic() < 1) return;
	      amt = -1*c1->getOrigCost();
	    }
	    else {
	      if(m->enchants.size() == 0) return;
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    bool alive = m->receiveSpellFrom(c1);
	    if(!alive) bury(m);
	    getAP()->addMagic(amt);
	    getAP()->getHand().detach(i);
	  }else if(c1->getName() == "Disenchant") {
	    int amt = 0;
	    if(m->enchants.size() == 0){
	      cout << "Cannot play Disenchant on minion without enchantments." << endl;
	      return;
	    }
	    if (!testing) {
	      if(getAP()->getMagic() < 1) return;
	      amt = -1*c1->getOrigCost();
	    }else {
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    ActivatedAbilities *a = dynamic_cast<ActivatedAbilities *>(m);
	    if(m->enchants.size() > 0 && m->enchants[m->enchants.size()-1]->getName() == "Magicless"){
	      m->addMagicless(-1);
	    }
	    if (a) {
	      a->removeEnchantment();
	    } else {
	      m->removeEnchantment();
	    }
	    amt = -1*c1->getOrigCost() <= 0 ? 0 : -1*c1->getOrigCost();
	    getAP()->addMagic(amt);
	    getAP()->getHand().detach(i);
	  }
	}
  }//spell
}//ISS

  /*
    ==========================================
    ATTACK COMMANDS
    ==========================================
  */
void GameController::Attack(int i, int j) {
  --i;
  --j;

  //ERROR CHECKING
  int size1 = getAP()->getBoard().getMinions().size();
  int size2 = getNAP()->getBoard().getMinions().size();
  if (i >= size1 || i < 0 || j >= size2 || j < 0) {
    cout << "Invalid index chosen, cannot attack minion. Please try again." << endl;
    return;
  }
  //
  
  Minion *m1 = fetch(getAP(), i);
  Minion *m2 = fetch(getNAP(), j);
  bool alive1= (m1->receiveAttackFrom(m2, false));
  bool alive2= (m2->receiveAttackFrom(m1, false));
  m1->attacked();
  if (!alive1) bury(m1);
  if (!alive2) bury(m2);
}

void GameController::Attack(int i) {
  --i;
  int size = getAP()->getBoard().getMinions().size();

  //ERROR CHECKING
  if (i >= size || i < 0) {
    cout << "Invalid index chosen, cannot attack owner. Please try again." << endl;
    return;
  }
  //
  
  vector<Minion *> mins = getNAP()->getBoard().getMinions();
  int existGuard = -1;
  for (int i = 0; i < mins.size(); i++){
    if(mins[i]->getName() == "Guardian"){
      existGuard = i;
      break;
    }
  }
  if(existGuard >= 0){
    Attack(i, existGuard);
  }else{
    Minion *c = fetch(getAP(), i);
    int n = c->getCurrAttack();
    getNAP()->addHealth(-n);
    c->attacked();
  }
  
}


  
