#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <memory>
#include <vector>
#include "gameViewController.h"
#include "../viewController/concreteTextViewController.h"
#include "../player/player.h"
#include "../board/board.h" 
#include "../dice/dice.h"
#include <map>
#include <fstream>

class GameViewController;

class GameModel
{
  std::vector<std::unique_ptr<Player>> players;

  std::unique_ptr<Board> board;

  int currentTurn;

  std::unique_ptr<GameViewController> gameViewController;



  const static int NUMPLAYERS = 4;

public:


  void initialize(const unsigned int seed = 0); //creates/initializes board and player

  void initializeFromFile(std::ifstream & boardFile); //creates/initializes board and player

  void initializeFromGameState(std::ifstream & gameFile);  //creates/initializes board and player

  int rollDice() const;

  Player *checkWinner() const;

  bool runGame(bool setUpAlready);

  void save(std::string outputFileName) const;

  void saveAndQuit(std::string outputFileName);

  void quit();

  GameModel(); // DOES NOT CREATE BOARD AND PLAYER AND DICE, BOARD GETS CREATED WHEN INITIALIZEBOARD GETS CALLED, BOARD IS NULLPTR HERE


  friend class ConcreteTextViewController;
};

#endif
