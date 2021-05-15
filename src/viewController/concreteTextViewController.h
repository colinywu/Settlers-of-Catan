#ifndef CONCRETETEXTVIEWCONTROLLER_H
#define CONCRETETEXTVIEWCONTROLLER_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include "../player/playerColour.h"
#include "../vertex/vertexType.h"
#include <memory>
#include <vector>
#include "../dice/concreteFairDice.h"
#include "../dice/concreteLoadedDice.h"

#include "./gameViewController.h"
#include "../model/gameModel.h"

class Dice;

struct EOFException : public std::exception
{
  const char *what() const throw()
  {
    return "End of line detected.";
  }
};

class ConcreteTextViewController : public GameViewController
{

  std::ostringstream printVertex(int location);
  std::ostringstream printNumber(int number);
  std::ostringstream printHorizontalEdge(int location);
  std::ostringstream printVerticalEdge(int location);
  std::ostringstream printCeilingLayer(int layer);
  std::ostringstream printValue(int value);
  std::ostringstream printWallLayer(int layer);
  std::ostringstream printEdgeLayer(int layer);
  std::ostringstream printBuffer(int layer);
  std::ostringstream printNameOnVertex(PlayerColour colour, VertexType buildingType);
  std::ostringstream printNameOnEdge(PlayerColour colour);
  std::ostringstream printTypeLayer(int layer);
  std::ostringstream printTileType(int location);
  std::ostringstream printGeese(int location);

  static const int numLayers = 11;
  int layersNumEdges[numLayers] = {1, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1};
  static const int BOXWIDTH = 10;
  static const int MAXNUMDIGITS = 2;
  const int MAXNUMEDGES = *(std::max_element(layersNumEdges, layersNumEdges + numLayers));
  static const int FIRSTFULLWIDTHLAYER = 2;
  static const int LASTFULLWIDTHLAYER = 8;

  int vertexNumber;
  int edgeNumber;
  int tileNumber;
  int tileValueNumber;
  int tileTypeNumber;
  int tileGooseNumber;

  static std::string playerColourEnumToString(PlayerColour colour);

  static std::string resourceTypeEnumToString(ResourceType type);

public:
  virtual void printBoard() override;

  virtual bool getTradeInput(Player &proposor, Player &proposed, ResourceType proposorType, ResourceType proposedType) const override;

  virtual std::vector<std::string> getDuringTurnInput() const override;

  virtual std::unique_ptr<Dice> getDiceVersionInput() const override;

  virtual int getLoadedDiceInput() const override;

  virtual int getInitialBuildResidenceLocation(const Player &player) const override;

  virtual int getNewGooseLocation() const override;

  virtual Player &getStealFromWho(std::vector<Player *> options, Player &player) const override;

  virtual void printError(const std::exception &e) const override;

  virtual void printNoBuildersToStealFrom(Player &player) const override;

  virtual void printGeeseMessage(Player &loser, int numRemoval) const override;

  virtual void printGeeseLostResources(int numResource, ResourceType resourceName) const override;

  virtual void printRobPlayer(Player &robber, ResourceType resource, Player &victim) const override;

  virtual void printTurnAndStatus(const Player &player) const override; //prints its builder <colours> turn followed by the status of the builder

  virtual void printStatus() const override;

  virtual void printResidences(const Player &player) const override;

  virtual void printRollAmt(int rollAmt) const override;

  virtual void printRollDiceHelp() const override;

  virtual void printSave(std::string outputFileName) const override;

  virtual void printResults() const override; //prints the resources that all players gets after diceRoll

  virtual void printHelp() const override;

  virtual void printSuccessfulRoad() const override;

  virtual void printSuccessfulBuilding() const override;

  void printWinner(const Player &player) const override;

  virtual void printSuccessfulImprovement() const override;

  bool getPlayAgain() const override;

  ConcreteTextViewController(GameModel *game);
};

#endif
