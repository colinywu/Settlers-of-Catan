#ifndef CONCRETELOADEDDICE_H
#define CONCRETELOADEDDICE_H

#include "dice.h"
#include "../viewController/gameViewController.h"



class GameViewController;

class ConcreteLoadedDice:public Dice
{

  const GameViewController * gameViewController;

public:
  virtual int rollDice() const override;

  ConcreteLoadedDice(const GameViewController * gameViewController, unsigned int seed);
};

#endif
