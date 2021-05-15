#ifndef CONCRETEFAIRDICE_H
#define CONCRETEFAIRDICE_H

#include "dice.h"
#include <vector>
#include <random>
#include <algorithm>

class ConcreteFairDice: public Dice {

  

public:
  virtual int rollDice() const override;
  ConcreteFairDice(unsigned int seed);
};

#endif
