#ifndef STATUS_H
#define STATUS_H
#include <map>

class Edge;

class Vertex;

class Status {
  
  int numEnergies;
  int numBricks;
  int numGlass;
  int numHeat;
  int numWifi;
  int queueEnergies;
  int queueBricks;
  int queueGlass;
  int queueHeat;
  int queueWifi;

  std::vector<int> ownedRoadLocation;
  std::vector<int> ownedBuildingLocation;

  std::map<int, Edge *> ownedRoads; //not a reference because c++ does not allow vector/map of references. DO NOT CHANGE

  std::map<int, Vertex *> ownedBuildings; //DO NOT CHANGE THE POINTER AFTER IT IS ADDED, TREAT AS A REFERENCE

public:
  int getTotalNumResource() const;

  int getLongestRoad() const;

  int getNumBuildings() const;

  int getBuildingPoints() const;

  void flushQueue();

  Status(int numEnergies, int numBricks, int numGlass, int numHeat, int numWifi, std::map<int, Edge *> ownedRoads, std::map<int, Vertex *> ownedBuildings);

  Status();

  friend class Vertex;
  friend class Player;
  friend class ConcreteTextViewController;
  friend class Board;
  friend class GameModel;
};

#endif
