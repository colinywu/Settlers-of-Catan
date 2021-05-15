#ifndef EDGE_H
#define EDGE_H

#include "../player/player.h"
#include "../vertex/vertex.h"


class Player;

class Vertex;


class Edge {

  friend class ConcreteTextViewController;

  const Player * owner;
  Vertex * connectedFrom;
  Vertex * connectedTo;
  const int location;

  public:
    Edge(const int location, Vertex * connectedFrom, Vertex * connectedTo);

    bool canBuildRoad(Player & player) const;

    bool isRoad() const;

    friend class Board;
    friend class Vertex;
    friend class GameModel;
};

#endif