#ifndef RESOURCETILE_H
#define RESOURCETILE_H

#include "subject.h"
#include "../vertex/vertex.h"
#include "./resourceType.h"
#include <algorithm>


class Player;
class ConcreteTextViewController;

class ResourceTile : public Subject {
  ResourceType type;

  bool hasGoose;

  int value;

  const int location;

public:
  ResourceTile(const int location, const bool hasGoose = false);

  ResourceTile(const int location, const ResourceType type, const bool hasGoose = false);

  void giveResourceIfNoGoose();

  std::vector<Player *> getPlayersOnIt() const;

  std::vector<Player *> getPlayersOnItThatCanBeRobbedByPlayer(Player & robberPlayer) const;

  virtual ResourceType getType() const override;

  friend class ConcreteTextViewController;
  friend class Board;
  friend class GameModel;
};

#endif
