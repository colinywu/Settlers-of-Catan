#include "vertex.h"
#include "../resourceTile/resourceType.h"
using namespace std;

Vertex::Vertex(const int location) : location{location}, type{VertexType::NONE}, owner{nullptr} {}

void Vertex::notify(Subject &whoNotified)
{
    if (checkOwner() != nullptr)
    {
        ResourceType tempResource = whoNotified.getType();
        int amount = 1;

        if (type == VertexType::HOUSE)
        {
            amount += 1;
        }
        else if (type == VertexType::TOWER)
        {
            amount += 2;
        }

        if (tempResource == ResourceType::BRICK)
        {
            owner->status.numBricks += amount;
            owner->status.queueBricks += amount;
        }
        else if (tempResource == ResourceType::ENERGY)
        {
            owner->status.numEnergies += amount;
            owner->status.queueEnergies += amount;
        }
        else if (tempResource == ResourceType::HEAT)
        {
            owner->status.numHeat += amount;
            owner->status.queueHeat += amount;
        }
        else if (tempResource == ResourceType::WIFI)
        {
            owner->status.numWifi += amount;
            owner->status.queueWifi += amount;
        }
        else if (tempResource == ResourceType::GLASS)
        {
            owner->status.numGlass += amount;
            owner->status.queueGlass += amount;
        }
        else
        {
            return;
        }
    }
}

Player *Vertex::checkOwner() const
{
    return owner;
}

bool Vertex::canBuild(const Player &player, bool isNewGame) const
{
    if (owner != nullptr)
    {
        return false;
    }

    for (auto &edge : connectedEdges)
    {
        if (edge->connectedFrom->checkOwner() != nullptr)
        {
            return false;
        }

        if (edge->connectedTo->checkOwner() != nullptr)
        {
            return false;
        }
    }

    if (isNewGame)
    {
        return true;
    }

    for (auto &edge : connectedEdges)
    {
        if (edge->owner == &player)
        {
            return true;
        }
    }

    return false;
}

bool Vertex::canUpgrade(const Player &player) const
{
    if (owner == nullptr)
    {
        return false;
    }

    if (owner != &player)
    {
        return false;
    }

    if (type == VertexType::TOWER)
    {
        return false;
    }

    if (type == VertexType::BASEMENT)
    {
        if (owner->status.numGlass < 2 && player.status.numHeat < 3)
        {
            return false;
        }
    }

    if (type == VertexType::HOUSE)
    {
        if (owner->status.numBricks < 3 && owner->status.numEnergies < 2 &&
            owner->status.numGlass < 2 && owner->status.numWifi < 1 && owner->status.numHeat < 2)
        {
            return false;
        }
    }

    return true;
}
