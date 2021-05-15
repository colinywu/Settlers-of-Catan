#include "edge.h"
using namespace std;

// unconfirmed -- seems good.
Edge::Edge(const int location, Vertex *connectedFrom, Vertex *connectedTo) : connectedFrom{connectedFrom}, connectedTo{connectedTo}, location{location}
{
  owner = nullptr;
}

// unconfirmed -- seems good.
bool Edge::canBuildRoad(Player &player) const
{
  // doesn't already have a road built on the edge
  if (owner != nullptr)
  {
    return false;
  }
  else
  {
    // check if adjacent vertices have the player's buildings
    if (connectedFrom->checkOwner() == &player || connectedTo->checkOwner() == &player)
    {
      return true;
    }
    else
    {
      // check if there is a road connecting to this edge.

      for (int i = 0; i < connectedFrom->connectedEdges.size(); i++)
      {
        if (connectedFrom->connectedEdges[i]->owner == &player)
        {
          return true;
        }
      }

      for (int i = 0; i < connectedTo->connectedEdges.size(); i++)
      {
        if (connectedTo->connectedEdges[i]->owner == &player)
        {
          return true;
        }
      }

      return false;
    }
  }
}

bool Edge::isRoad() const
{
  return owner != nullptr;
}
