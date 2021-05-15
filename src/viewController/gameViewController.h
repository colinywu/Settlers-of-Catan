#ifndef GAMEVIEWCONTROLLER_H
#define GAMEVIEWCONTROLLER_H

#include <string>
#include "../player/playerColour.h"
#include "../dice/dice.h"
#include "../player/player.h"
#include <stdexcept>

class GameModel;

class GameViewController
{

  protected:
  
  const GameModel * game;

public:


  virtual void printBoard() = 0;

  virtual bool getTradeInput(Player & proposor, Player & proposed, ResourceType proposorType, ResourceType proposedType) const = 0;

  virtual std::vector<std::string> getDuringTurnInput() const = 0;

  virtual std::unique_ptr<Dice> getDiceVersionInput() const = 0;

  virtual int getLoadedDiceInput() const = 0;

  virtual int getInitialBuildResidenceLocation(const Player &player) const = 0; //only used to build first basements, later on use getDuringTurnInput

  virtual int getNewGooseLocation() const = 0;

  virtual bool getPlayAgain() const = 0;

  virtual Player & getStealFromWho(std::vector<Player *> options, Player & player) const = 0;

  virtual void printError(const std::exception & e) const = 0;

  virtual void printNoBuildersToStealFrom(Player & player) const = 0;

  virtual void printGeeseMessage(Player & loser, int numRemoval) const = 0;

  virtual void printGeeseLostResources(int numResource, ResourceType resourceName) const = 0;

  virtual void printRobPlayer(Player & robber, ResourceType resource, Player & victim) const = 0;
  
  virtual void printStatus() const = 0;

  virtual void printTurnAndStatus(const Player & player) const = 0; //prints its builder <colours> turn followed by the status of the builder

  virtual void printResidences(const Player &player) const = 0;

  virtual void printRollAmt(int rollAmt) const = 0;

  virtual void printRollDiceHelp() const = 0;
  
  virtual void printResults() const = 0;

  virtual void printSave(std::string outputFileName) const = 0;

  virtual void printHelp() const = 0;


  virtual void printSuccessfulRoad() const = 0;

  virtual void printSuccessfulBuilding() const = 0;

  virtual void printSuccessfulImprovement() const = 0;

  virtual void printWinner(const Player & player) const = 0;

  GameViewController(GameModel *game);

  virtual ~GameViewController() = default;
};

#endif
