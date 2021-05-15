#include <map>
#include "../vertex/vertex.h"
#include "../vertex/vertexType.h"
#include "status.h"

Status::Status(int numEnergies, int numBricks, int numGlass, int numHeat, int numWifi, std::map<int, Edge *> ownedRoads, std::map<int, Vertex *> ownedBuildings) : numEnergies{numEnergies}, numBricks{numBricks}, numGlass{numGlass}, numHeat{numHeat}, numWifi{numWifi}, ownedRoads{ownedRoads}, ownedBuildings{ownedBuildings}, queueEnergies{0}, queueBricks{0}, queueGlass{0}, queueHeat{0}, queueWifi{0} {};

Status::Status() : numEnergies{0}, numBricks{0}, numGlass{0}, numHeat{0}, numWifi{0}, queueEnergies{0}, queueBricks{0}, queueGlass{0}, queueHeat{0}, queueWifi{0} {};

int Status::getTotalNumResource() const
{
  return numEnergies + numBricks + numGlass + numHeat + numWifi;
}

// have to do some graph theory stuff
int Status::getLongestRoad() const
{
  return 0;
}

int Status::getNumBuildings() const
{
  return ownedBuildings.size();
}

int Status::getBuildingPoints() const
{
  int counter = 0;
  for (auto const &building : ownedBuildings)
  {
    if (building.second->type == VertexType::BASEMENT)
    {
      counter++;
    }
    if (building.second->type == VertexType::HOUSE)
    {
      counter += 2;
    }
    if (building.second->type == VertexType::TOWER)
    {
      counter += 3;
    }
  }
  return counter;
}

void Status::flushQueue()
{
  queueEnergies = 0;
  queueBricks = 0;
  queueGlass = 0;
  queueHeat = 0;
  queueWifi = 0;
}
