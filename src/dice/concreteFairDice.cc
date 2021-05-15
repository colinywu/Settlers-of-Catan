#include "concreteFairDice.h"

//TODO: implement
int ConcreteFairDice::rollDice() const
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 6);
  int dice1 = dis(gen);
  int dice2 = dis(gen);
  return dice1 + dice2;
}

ConcreteFairDice::ConcreteFairDice(unsigned int seed) : Dice{seed} {};