#ifndef DICE_H
#define DICE_H

class Dice
{
protected:
  unsigned int seed;

public:
  virtual int rollDice() const = 0;

  virtual ~Dice() = default;

  Dice(unsigned int seed);
};

#endif
