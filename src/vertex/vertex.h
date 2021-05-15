#ifndef VERTEX_H
#define VERTEX_H

#include "vertexType.h"
#include "../player/player.h"
#include "../edge/edge.h"
#include "observer.h"
#include "../resourceTile/subject.h"

class Player;

class Edge;

class Vertex : public Observer {
  VertexType type;
  Player * owner;
  const int location;
  std::vector<Edge *> connectedEdges;

public:
  Vertex(const int location);

  virtual void notify(Subject &whoNotified) override; // once being notified by its subject (resourceTile), allocates resources to the player who's built around it

  Player * checkOwner() const;

  bool canBuild(const Player & player, bool isNewGame) const;

  bool canUpgrade(const Player & player) const;

  friend class ConcreteTextViewController;
  friend class Edge;
  friend class Board;
  friend class Status;
  friend class Player;
  friend class GameModel;

  //if beginning of game, still check if there's vertex there. jsut skip the test if there's already owner/if there's already house.
  //runGame passes boolean, put in boolean for these methods and arguments. figure out which method needs the boolean, THEN UPDATE UML.
};

#endif
