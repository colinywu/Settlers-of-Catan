#include "concreteLoadedDice.h"


ConcreteLoadedDice::ConcreteLoadedDice(const GameViewController * gameViewController, unsigned int seed): Dice{seed}, gameViewController{gameViewController}{};

//TODO: implement
 int ConcreteLoadedDice::rollDice() const{
   return gameViewController->getLoadedDiceInput();
 }