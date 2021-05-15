#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "status.h"
#include "../vertex/vertex.h"
#include "../vertex/vertexType.h"
#include "../board/board.h"
#include "playerColour.h"
#include "../viewController/gameViewController.h"
#include "../dice/concreteLoadedDice.h"

class ConcreteTextViewController;

class GameViewController;

class Board;

class Status;

class Player {
  Board * board;

  Status status;

  PlayerColour colour;

  GameViewController * gameViewController;

    std::unique_ptr<Dice> dice; //null until rollDice


  std::string playerColourEnumToString(PlayerColour colour);
  void throwErrorifNohasResource(Player & trader, Player & recipient, const ResourceType give, const ResourceType receive);

  public:
    Player(Board * board, PlayerColour colour, GameViewController * GameViewController);

    Player(Board * board, PlayerColour colour, GameViewController * GameViewController, Status status);

    void proposeTrade(Player & recipient, 
      const ResourceType give, const ResourceType receive);

    bool respondTrade(Player & trader, 
    const ResourceType give, const ResourceType receive);

    std::vector<Vertex *> getResidences() const;

    void buildRoad(const int location);

    void buildResidence(const int location, bool isNewGame);

    void improveResidence(const int location);

    void tryRobbedByGoose();

    void robPlayer(Player & victim);

    bool moreThanTenCards() const;

    std::string getSerializedStatus() const;


    friend class ConcreteTextViewController;
    friend class Vertex;
    friend class GameModel;
    friend class Board;
    friend class ResourceTile;
};

#endif