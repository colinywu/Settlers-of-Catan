#include "string"
#include <stdlib.h>
#include <vector>
#include <exception>
#include "gameModel.h"

using namespace std;

GameModel::GameModel() : currentTurn{0}
{
  gameViewController = std::make_unique<ConcreteTextViewController>(this);
}

void GameModel::initialize(const unsigned int seed)
{
  currentTurn = 0;
  board = std::make_unique<Board>(seed);

  //initialize players
  for (int i = 0; i < NUMPLAYERS; i++)
  {

    PlayerColour colour;

    switch (i)
    {
    case 0:
      colour = PlayerColour::BLUE;
      break;
    case 1:
      colour = PlayerColour::RED;
      break;
    case 2:
      colour = PlayerColour::ORANGE;
      break;
    case 3:
      colour = PlayerColour::YELLOW;
      break;
    default:
      break;
    }

    std::unique_ptr<Player> temp = std::make_unique<Player>(board.get(), colour, gameViewController.get());
    players.push_back(std::move(temp));
  }
}

void GameModel::initializeFromFile(std::ifstream &boardFile)
{
  currentTurn = 0;
  board = std::make_unique<Board>(boardFile);

  //initialize players
  for (int i = 0; i < NUMPLAYERS; i++)
  {

    PlayerColour colour;

    switch (i)
    {
    case 0:
      colour = PlayerColour::BLUE;
      break;
    case 1:
      colour = PlayerColour::RED;
      break;
    case 2:
      colour = PlayerColour::ORANGE;
      break;
    case 3:
      colour = PlayerColour::YELLOW;
      break;
    default:
      break;
    }

    std::unique_ptr<Player> temp = std::make_unique<Player>(board.get(), colour, gameViewController.get());
    players.push_back(std::move(temp));
  }
}

void GameModel::initializeFromGameState(std::ifstream &gameFile)
{

  gameFile >> currentTurn;

  if ((currentTurn < 0) || (currentTurn > 3))
  {
    throw invalid_argument("Invalid current turn.");
  }

  std::vector<std::string> builderDataString;

  std::string dummy;

  std::getline(gameFile, dummy);

  for (int i = 0; i < NUMPLAYERS; i++)
  {
    std::string line;
    std::getline(gameFile, line);
    builderDataString.push_back(line);
  }

  std::string boardLine;

  std::getline(gameFile, boardLine);

  std::istringstream boardLiness{boardLine};

  string inputString;

  int geeseLocation;

  try
  {
    gameFile >> inputString;
    geeseLocation = stoi(inputString);
  }
  catch (const invalid_argument &error)
  {
    throw invalid_argument("Invalid geeseLocation.");
  }

  if (((geeseLocation < 0) || (geeseLocation > 18)) && (geeseLocation != -1))
  {
    throw invalid_argument("Invalid geeseLocation");
  }

  //initialize board

  board = std::make_unique<Board>(boardLiness);

  //geese

  if (geeseLocation = -1)
  {
    board->gooseLocation = nullptr;
  }
  else
  {
    board->gooseLocation = board->tiles.at(geeseLocation).get();

    board->tiles.at(geeseLocation)->hasGoose = true;
  }

  for (int i = 0; i < builderDataString.size(); i++)
  {
    int numBricks;
    int numEnergies;
    int numGlass;
    int numHeat;
    int numWifi;

    std::istringstream builderDataStringStream{builderDataString.at(i)};
    try
    {
      builderDataStringStream >> inputString;
      numBricks = stoi(inputString);
      builderDataStringStream >> inputString;
      numEnergies = stoi(inputString);
      builderDataStringStream >> inputString;
      numGlass = stoi(inputString);
      builderDataStringStream >> inputString;
      numHeat = stoi(inputString);
      builderDataStringStream >> inputString;
      numWifi = stoi(inputString);
    }
    catch (const invalid_argument &error)
    {
      throw invalid_argument("Invalid player data.");
    }

    char roadIndicator;

    builderDataStringStream >> roadIndicator;

    if (roadIndicator != 'r')
    {
      throw invalid_argument("Missing Road Indicator");
    }

    std::string roadLocTemp;
    std::map<int, Edge *> ownedRoads;
    while (builderDataStringStream >> roadLocTemp && roadLocTemp != "h")
    {
      std::stringstream roadLocSS{roadLocTemp};
      int roadLoc;

      try
      {
        roadLocSS >> inputString;
        roadLoc = stoi(inputString);
      }
      catch (const invalid_argument &error)
      {
        throw invalid_argument("Invalid Road Location");
      }

      try
      {
        ownedRoads.insert(std::pair<int, Edge *>(roadLoc, board.get()->edges.at(roadLoc).get()));
      }
      catch (std::exception &e)
      {
        gameViewController.get()->printError(e);
      }
    }

    std::string housingLocTemp;
    std::map<int, Vertex *> ownedHousings;
    while (builderDataStringStream >> housingLocTemp)
    {
      std::stringstream housingLocSS{housingLocTemp};
      int housingLoc;

      try
      {
        housingLocSS >> inputString;
        housingLoc = stoi(inputString);
      }
      catch (const invalid_argument &error)
      {
        throw invalid_argument("Invalid Housing Location");
      }

      char housingType;
      builderDataStringStream >> housingType;
      VertexType type;
      switch (housingType)
      {
      case 'B':
        type = VertexType::BASEMENT;
        break;
      case 'H':
        type = VertexType::HOUSE;
        break;
      case 'T':
        type = VertexType::TOWER;
        break;
      default:
        throw invalid_argument("Invalid Housing");
        break;
      }
      try
      {
        ownedHousings.insert(std::pair<int, Vertex *>(housingLoc, board.get()->vertices.at(housingLoc).get()));
        board.get()->vertices.at(housingLoc).get()->type = type;
      }
      catch (std::exception &e)
      {
        gameViewController.get()->printError(e);
      }
    }

    PlayerColour colour;

    switch (i)
    {
    case 0:
      colour = PlayerColour::BLUE;
      break;
    case 1:
      colour = PlayerColour::RED;
      break;
    case 2:
      colour = PlayerColour::ORANGE;
      break;
    case 3:
      colour = PlayerColour::YELLOW;
      break;
    default:
      //TODO: throw exception
      break;
    }
    Status tempStatus = Status{numEnergies, numBricks, numGlass, numHeat, numWifi, ownedRoads, ownedHousings};
    std::unique_ptr<Player> temp = std::make_unique<Player>(board.get(), colour, gameViewController.get(), tempStatus);

    players.push_back(std::move(temp));

    for (auto const &road : ownedRoads)
    {
      road.second->owner = players.at(i).get();
    }

    for (auto const &road : ownedHousings)
    {
      road.second->owner = players.at(i).get();
    }
  }
}

bool GameModel::runGame(bool setUpAlready)
{

  //fills the board with player houses in beginning
  try
  {
    if (!setUpAlready)
    {
      for (int i = 0; i < players.size(); i++)
      {
        gameViewController.get()->printBoard();
        bool proceed = false;
        while (!proceed)
        {
          try
          {
            int location = gameViewController.get()->getInitialBuildResidenceLocation(*(players.at(i).get())); //dereferencing but passing as the address to that deferenced value -> original pointer
            board.get()->addResidence(location, *(players.at(i).get()), true);
            proceed = true;
          }
          catch (std::invalid_argument &ia)
          {
            gameViewController.get()->printError(ia);
          }
        }
      }

      for (int i = players.size() - 1; i > -1; i--)
      {
        gameViewController.get()->printBoard();
        bool proceed = false;
        while (!proceed)
        {
          try
          {
            int location = gameViewController.get()->getInitialBuildResidenceLocation(*(players.at(i))); //dereferencing but passing as the address to that deferenced value -> original pointer
            board.get()->addResidence(location, *(players.at(i).get()), true);
            proceed = true;
          }
          catch (std::invalid_argument &ia)
          {
            gameViewController.get()->printError(ia);
          }
        }
      }
    }
  }
  catch (EOFException &e)
  {
    gameViewController->printError(e);

    return false;
  }

  //begins play

  while (true)
  {
    try
    {
      gameViewController.get()->printBoard();

      gameViewController.get()->printTurnAndStatus(*(players.at(currentTurn)));

      std::unique_ptr<Dice> tempDice = gameViewController.get()->getDiceVersionInput();

      if (tempDice)
      {
        players.at(currentTurn)->dice = std::move(tempDice);
      }

      int rollAmt = players.at(currentTurn)->dice.get()->rollDice();

      gameViewController.get()->printRollAmt(rollAmt);

      board->activateResourceTile(rollAmt);

      if (rollAmt == 7)
      {
        for (auto &player : players)
        {
          player->tryRobbedByGoose();
        }

        int newGooseLocation = gameViewController->getNewGooseLocation();

        board->moveGooseTo(*(board->tiles.at(newGooseLocation)));

        std::vector<Player *> victimOptions = board->tiles.at(newGooseLocation)->getPlayersOnItThatCanBeRobbedByPlayer(*(players.at(currentTurn)));

        if (victimOptions.size())
        {
          Player &victim = gameViewController->getStealFromWho(victimOptions, *(players.at(currentTurn)));

          players.at(currentTurn)->robPlayer(victim);
        }
        else
        {
          gameViewController->printNoBuildersToStealFrom(*(players.at(currentTurn)));
        }
        gameViewController.get()->printBoard();
      }
      else
      {
        gameViewController->printResults();
      }

      for (auto &player : players)
      {
        player->status.flushQueue();
      }

      //during turn

      while (true)
      {
        try
        {
          std::vector<std::string> option = gameViewController->getDuringTurnInput();

          std::string indicator = option.at(0);

          if (indicator == "board")
          {
            gameViewController->printBoard();
          }
          else if (indicator == "status")
          {
            gameViewController->printStatus();
          }
          else if (indicator == "residences")
          {
            gameViewController->printResidences(*(players[currentTurn].get()));
          }
          else if (indicator == "build-road")
          {
            unsigned int location = std::stoi(option.at(1));
            players[currentTurn].get()->buildRoad(location);
          }
          else if (indicator == "build-res")
          {
            unsigned int location = std::stoi(option.at(1));
             players[currentTurn].get()->buildResidence(location,false);
        
          }
          else if (indicator == "improve")
          {
            unsigned int location = std::stoi(option.at(1));
            
              players[currentTurn].get()->improveResidence(location);

          }
          else if (indicator == "trade")
          {
            Player *subject;
            if (option.at(1) == "Blue")
            {
              subject = players.at(0).get();
            }
            else if (option.at(1) == "Red")
            {
              subject = players.at(1).get();
            }
            else if (option.at(1) == "Orange")
            {
              subject = players.at(2).get();
            }
            else if (option.at(1) == "Yellow")
            {
              subject = players.at(3).get();
            }
            else
            {
              //do nothing
            }

            ResourceType give;
            if (option.at(2) == "Brick")
            {
              give = ResourceType::BRICK;
            }
            else if (option.at(2) == "Energy")
            {
              give = ResourceType::ENERGY;
            }
            else if (option.at(2) == "Glass")
            {
              give = ResourceType::GLASS;
            }
            else if (option.at(2) == "Heat")
            {
              give = ResourceType::HEAT;
            }
            else if (option.at(2) == "Wifi")
            {
              give = ResourceType::WIFI;
            }
            else
            {
              //do nothing
            }

            ResourceType recieve;
            if (option.at(3) == "Brick")
            {
              recieve = ResourceType::BRICK;
            }
            else if (option.at(3) == "Energy")
            {
              recieve = ResourceType::ENERGY;
            }
            else if (option.at(3) == "Glass")
            {
              recieve = ResourceType::GLASS;
            }
            else if (option.at(3) == "Heat")
            {
              recieve = ResourceType::HEAT;
            }
            else if (option.at(3) == "Wifi")
            {
              recieve = ResourceType::WIFI;
            }
            else
            {
              //do nothing
            }

            players.at(currentTurn)->proposeTrade(*subject, give, recieve);
          }
          else if (indicator == "next")
          {
            if (checkWinner())
            {
              gameViewController->printWinner(*(players.at(currentTurn)));

              return gameViewController->getPlayAgain();
            }
            currentTurn = (currentTurn + 1) % NUMPLAYERS;
            break;
          }
          else if (indicator == "save")
          {

            save(option.at(1));
          }
          else if (indicator == "help")
          {
            gameViewController->printHelp();
          }
        }
        catch (invalid_argument &e)
        {
          gameViewController->printError(e);
          continue;
        }
      }
    }
    catch (EOFException &e)
    {
      gameViewController->printError(e);
      save("backup.sv");
      return false;
    }
  }
}

Player *GameModel::checkWinner() const
{
  for (int i = 0; i < 4; i++)
  {
    if (players[i]->status.getBuildingPoints() >= 10)
    {
      return players[i].get();
    }
  }
  return nullptr;
}

void GameModel::save(std::string outputFileName) const
{

  gameViewController->printSave(outputFileName);

  std::ofstream gameFile{outputFileName};

  gameFile << std::to_string(currentTurn) << std::endl;
  for (int i = 0; i < players.size(); i++)
  {
    gameFile << players.at(i)->getSerializedStatus() << std::endl;
  }

  gameFile << board->getSerializedBoard() << std::endl;

  gameFile << board->getSerializedGooseLocation() << std::endl;
}
