#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include "../resourceTile/resourceTile.h"
#include <iostream>

class Player;

class ResourceTile;


class Board {
  std::vector<std::unique_ptr<ResourceTile>> tiles;

  std::vector<std::unique_ptr<Vertex>> vertices;

  ResourceTile *gooseLocation;

  std::vector<std::unique_ptr<Edge>> edges;

  unsigned int seed;

public:

  void moveGooseTo(ResourceTile & tile);

  void activateResourceTile(const int rollNumber);

  void addRoad(const unsigned int location, Player & builder);

  void addResidence(const unsigned int location, Player & builder, bool isNewGame);

  void improveResidence(const unsigned int location, Player & builder);
  
  std::string getSerializedBoard();

  std::string getSerializedGooseLocation();

  Board(const unsigned int seed);

  Board(std::istream & boardStream);
  
  friend class ConcreteTextViewController;
  friend class Player;
  friend class GameModel;

  
};

#endif
