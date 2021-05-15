#include "resourceTile.h"
using namespace std;

//TODO: Change tyoe and value to be random
ResourceTile::ResourceTile(const int location, const bool hasGoose) : location{location}, type{ResourceType::PARK}, hasGoose{hasGoose}, value{2} {}

ResourceTile::ResourceTile(const int location, const ResourceType type, const bool hasGoose) : location{location}, type{type}, hasGoose{hasGoose} {}

void ResourceTile::giveResourceIfNoGoose()
{
    if (hasGoose)
    {
        return;
    }

    notifyObservers();
}

vector<Player *> ResourceTile::getPlayersOnIt() const
{
    vector<Player *> players;

    for (auto player : getObservers())
    {
        auto vertex = static_cast<Vertex *>(player);
        if (vertex->checkOwner() != nullptr)
        {
            players.push_back(vertex->checkOwner());
        }
    }

    return players;
}

vector<Player *> ResourceTile::getPlayersOnItThatCanBeRobbedByPlayer(Player &robberPlayer) const
{
    vector<Player *> players;

    for (auto player : getObservers())
    {
        auto vertex = static_cast<Vertex *>(player);
        if ((vertex->checkOwner() != nullptr) && (vertex->checkOwner() != &robberPlayer) && (vertex->checkOwner()->status.getTotalNumResource() > 0))
        {
            players.push_back(vertex->checkOwner());
        }
    }

    return players;
}

ResourceType ResourceTile::getType() const
{
    return type;
}
