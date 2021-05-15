#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include "concreteTextViewController.h"
#include <stdexcept>
using namespace std;

ConcreteTextViewController::ConcreteTextViewController(GameModel *game) : GameViewController(game), vertexNumber{0}, edgeNumber{0}, tileNumber{0}, tileValueNumber{0}, tileTypeNumber{0}, tileGooseNumber{0} {};

void ConcreteTextViewController::printBoard()
{
  for (int i = 0; i < numLayers; i++)
  {
    std::cout << printCeilingLayer(i).str() << std::endl;

    std::cout << printWallLayer(i).str() << std::endl;
    std::cout << printEdgeLayer(i).str() << std::endl;

    std::cout << printTypeLayer(i).str() << std::endl;
  }

  vertexNumber = 0;
  edgeNumber = 0;
  tileNumber = 0;
  tileValueNumber = 0;
  tileTypeNumber = 0;
  tileGooseNumber = 0;
}

std::ostringstream ConcreteTextViewController::printTypeLayer(int layer)
{

  std::ostringstream output;

  if (layer == numLayers - 1)
  {
    return output;
  }

  if (layer >= LASTFULLWIDTHLAYER)
  {
    output << printBuffer(layer + 1).str();
    output << "  |         ";

    for (int i = 0; i < layersNumEdges[layer + 1] - 1; i++)
    {
      output << printTileType(game->board.get()->tiles[tileTypeNumber].get()->location).str();

      tileTypeNumber++;
      output << "         ";
    }

    output << "|";
    return output;
  }

  output << printBuffer(layer).str();

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << "  |       ";
  }

  output << "  ";
  output << printTileType(game->board.get()->tiles[tileTypeNumber].get()->location).str();
  tileTypeNumber++;

  for (int i = 0; i < layersNumEdges[layer] - 1; i++)
  {
    output << "       ";
    output << "  " << printTileType(game->board.get()->tiles[tileTypeNumber].get()->location).str();
    tileTypeNumber++;
  }

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << "         |";
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printTileType(int location)
{

  std::ostringstream output;

  std::string beginning = "|  ";
  output << beginning;

  int numTrailingWhiteSpace = BOXWIDTH - beginning.size();

  output << resourceTypeEnumToString(game->board.get()->tiles[location].get()->type);

  numTrailingWhiteSpace -= resourceTypeEnumToString(game->board.get()->tiles[location].get()->type).size();

  for (int i = 0; i < numTrailingWhiteSpace; i++)
  {
    output << " ";
  }

  output << "|";

  return output;
}

std::ostringstream ConcreteTextViewController::printBuffer(int layer)
{
  std::ostringstream output;
  if ((layersNumEdges[layer] < MAXNUMEDGES) && ((layer > LASTFULLWIDTHLAYER) || (layer < FIRSTFULLWIDTHLAYER)))
  {
    for (int i = 0; i < (MAXNUMEDGES - layersNumEdges[layer]) * BOXWIDTH; i++)
    {
      output << " ";
    }
  }
  return output;
}

std::ostringstream ConcreteTextViewController::printCeilingLayer(int layer)
{

  std::ostringstream output;

  output << printBuffer(layer).str();

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
    vertexNumber++;
    if (game->board->tiles.at(tileValueNumber)->type == ResourceType::PARK)
    {
      output << "      ";
    }
    else
    {
      output << printValue(game->board.get()->tiles[tileValueNumber].get()->value).str();
    }

    tileValueNumber++;
  }

  output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
  vertexNumber++;
  output << printHorizontalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
  edgeNumber++;
  output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
  vertexNumber++;

  for (int i = 0; i < layersNumEdges[layer] - 1; i++)
  {
    if (game->board->tiles.at(tileValueNumber)->type == ResourceType::PARK)
    {
      output << "      ";
    }
    else
    {
      output << printValue(game->board.get()->tiles[tileValueNumber].get()->value).str();
    }
    tileValueNumber++;
    output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
    vertexNumber++;
    output << printHorizontalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
    edgeNumber++;
    output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
    vertexNumber++;
  }

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    if (game->board->tiles.at(tileValueNumber)->type == ResourceType::PARK)
    {
      output << "      ";
    }
    else
    {
      output << printValue(game->board.get()->tiles[tileValueNumber].get()->value).str();
    }
    tileValueNumber++;
    output << printVertex(game->board.get()->vertices[vertexNumber].get()->location).str();
    vertexNumber++;
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printValue(int value)
{
  std::ostringstream output;
  output << "  " << printNumber(value).str() << "  ";
  return output;
}

std::ostringstream ConcreteTextViewController::printVertex(int location)
{

  std::ostringstream output;

  output << "|";
  if (game->board.get()->vertices[location]->checkOwner())
  {
    output << printNameOnVertex(game->board.get()->vertices[location]->checkOwner()->colour, game->board.get()->vertices[location]->type).str();
  }
  else
  {
    output << printNumber(location).str();
  }
  output << "|";
  return output;
}

std::ostringstream ConcreteTextViewController::printNameOnVertex(PlayerColour colour, VertexType buildingType)
{
  std::ostringstream output;

  if (colour == PlayerColour::BLUE)
  {
    output << "B";
  }
  else if (colour == PlayerColour::RED)
  {
    output << "R";
  }
  else if (colour == PlayerColour::ORANGE)
  {
    output << "O";
  }
  else if (colour == PlayerColour::YELLOW)
  {
    output << "Y";
  }
  else
  {
    throw invalid_argument{"Invalid command."};
  }

  if (buildingType == VertexType::BASEMENT)
  {
    output << "B";
  }
  else if (buildingType == VertexType::HOUSE)
  {
    output << "H";
  }
  else if (buildingType == VertexType::TOWER)
  {
    output << "T";
  }
  else
  {
    throw invalid_argument{"Invalid command."};
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printHorizontalEdge(int location)
{

  std::ostringstream output;

  output << "--";
  if ((game->board.get()->edges)[location].get()->owner)
  {
    output << printNameOnEdge((game->board.get()->edges)[location].get()->owner->colour).str();
  }
  else
  {
    output << printNumber(location).str();
  }

  output << "--";
  return output;
}

std::ostringstream ConcreteTextViewController::printVerticalEdge(int location)
{

  std::ostringstream output;

  if ((game->board.get()->edges)[location].get()->owner)
  {
    output << printNameOnEdge((game->board.get()->edges)[location].get()->owner->colour).str();
  }
  else
  {
    output << printNumber(location).str();
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printNameOnEdge(PlayerColour colour)
{
  std::ostringstream output;

  if (colour == PlayerColour::BLUE)
  {
    output << "B";
  }
  else if (colour == PlayerColour::RED)
  {
    output << "R";
  }
  else if (colour == PlayerColour::ORANGE)
  {
    output << "O";
  }
  else if (colour == PlayerColour::YELLOW)
  {
    output << "Y";
  }
  else
  {
    throw invalid_argument{"Invalid command."};
  }

  output << "R";

  return output;
}

std::ostringstream ConcreteTextViewController::printNumber(int number)
{
  std::ostringstream ss;
  ss << number;
  int digits = ss.str().size();
  std::ostringstream output;
  for (int i = 0; i < MAXNUMDIGITS - digits; i++)
  {
    //adds spacer to turn "0" into "_0"
    output << " ";
  }
  output << number;
  return output;
}

std::ostringstream ConcreteTextViewController::printEdgeLayer(int layer)
{
  std::ostringstream output;

  if (layer == numLayers - 1)
  {
    return output;
  }

  if (layer >= LASTFULLWIDTHLAYER)
  {
    output << printBuffer(layer + 1).str();
    output << " " << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str() << "        ";
    edgeNumber++;
    output << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
    edgeNumber++;

    for (int i = 0; i < layersNumEdges[layer + 1] - 1; i++)
    {
      output << "   " << printNumber(game->board.get()->tiles[tileNumber].get()->location).str() << "   ";

      tileNumber++;
      output << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str() << "        ";
      edgeNumber++;
      output << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
      edgeNumber++;
    }
    return output;
  }

  output << printBuffer(layer).str();

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << " " << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str() << "       ";
    edgeNumber++;
  }

  output << " " << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str() << "   " << printNumber(game->board.get()->tiles[tileNumber].get()->location).str() << "   ";
  edgeNumber++;
  tileNumber++;
  output << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
  edgeNumber++;

  for (int i = 0; i < layersNumEdges[layer] - 1; i++)
  {
    output << "       ";
    output << " " << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str() << "   " << printNumber(game->board.get()->tiles[tileNumber].get()->location).str() << "   ";
    edgeNumber++;
    tileNumber++;
    output << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
    edgeNumber++;
  }

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << "        " << printVerticalEdge(game->board.get()->edges[edgeNumber].get()->location).str();
    edgeNumber++;
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printWallLayer(int layer)
{
  std::ostringstream output;

  if (layer == numLayers - 1)
  {
    return output;
  }

  if (layer >= LASTFULLWIDTHLAYER)
  {
    output << printBuffer(layer + 1).str();
    output << "  |         ";

    for (int i = 0; i < layersNumEdges[layer + 1] - 1; i++)
    {
      output << printGeese(game->board.get()->tiles[tileGooseNumber].get()->location).str();

      tileGooseNumber++;
      output << "         ";
    }

    output << "|";
    return output;
  }

  output << printBuffer(layer).str();

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << "  |       ";
  }

  output << "  ";
  output << printGeese(game->board.get()->tiles[tileGooseNumber].get()->location).str();
  tileGooseNumber++;

  for (int i = 0; i < layersNumEdges[layer] - 1; i++)
  {
    output << "       ";
    output << "  " << printGeese(game->board.get()->tiles[tileGooseNumber].get()->location).str();
    tileGooseNumber++;
  }

  if (((layer >= FIRSTFULLWIDTHLAYER) && (layer <= LASTFULLWIDTHLAYER)) && (layersNumEdges[layer] == 2))
  {

    output << "         |";
  }

  return output;
}

std::ostringstream ConcreteTextViewController::printGeese(int location)
{

  std::ostringstream output;

  std::string geese = "GEESE";

  std::string beginning = "|  ";
  output << beginning;

  int numTrailingWhiteSpace = BOXWIDTH - beginning.size();

  if (game->board->tiles.at(tileGooseNumber)->hasGoose)
  {
    output << geese;

    numTrailingWhiteSpace -= geese.size();
  }
  else
  {
  }

  for (int i = 0; i < numTrailingWhiteSpace; i++)
  {
    output << " ";
  }

  output << "|";

  return output;
}

void ConcreteTextViewController::printTurnAndStatus(const Player &player) const
{
  std::cout << "||================================================================||" << std::endl;
  std::cout << "                     Builder " << playerColourEnumToString(player.colour) << "'s turn." << std::endl;
  std::cout << "||================================================================||" << std::endl;
  printStatus();
}

std::unique_ptr<Dice> ConcreteTextViewController::getDiceVersionInput() const
{
  std::cin.exceptions(std::ios::eofbit);

  std::string rollMethod = "";
  //current have ....
  while (true)
  {

    std::cout << "Specify loaded or fair dice, or roll (your previous choice is remembered so you can just roll directly" << std::endl;
    std::cout << " but you are provided with a loaded dice in the beginning of the round)" << std::endl;

    std::cout << "> ";

    std::string input;

    try
    {
      std::cin >> input;
    }
    catch (std::ios::failure e)
    {
      throw EOFException();
    }

    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });

    if (input == "load")
    {
      rollMethod = "load";

      std::cout << "Loaded dice selected" << std::endl;
    }
    else if (input == "fair")
    {
      rollMethod = "fair";

      std::cout << "Fair dice selected" << std::endl;
    }
    else if (input == "help")
    {
      printRollDiceHelp();
    }
    else if (input == "status")
    {
      printStatus();
    }
    else if (input == "roll")
    {
      break;
    }
    else
    {
      std::cerr << "Invalid command. Please enter 'help' for a list of valid commands." << std::endl;
    }
  }

  if (rollMethod == "load")
  {
    std::unique_ptr<Dice> dice = std::make_unique<ConcreteLoadedDice>(this, game->board.get()->seed); //moves it
    return dice;
  }
  else if (rollMethod == "fair")
  {
    //has to be fair dice;
    std::unique_ptr<Dice> dice = std::make_unique<ConcreteFairDice>(game->board.get()->seed);
    return dice;
  }
  else
  {
    return nullptr;
  }
}

bool ConcreteTextViewController::getTradeInput(Player &proposor, Player &proposed, ResourceType proposorType, ResourceType proposedType) const
{
  std::cin.exceptions(std::ios::eofbit);

  while (true)
  {

    std::cout << playerColourEnumToString(proposor.colour) << " offers " << playerColourEnumToString(proposed.colour) << " one " << resourceTypeEnumToString(proposorType)
              << " for one " << resourceTypeEnumToString(proposedType) << "." << std::endl;

    std::cout << "Does " << playerColourEnumToString(proposed.colour) << " accept this offer? (Yes|No)" << std::endl;

    std::string input;

    try
    {
      std::cin >> input;
    }
    catch (std::ios::failure e)
    {
      throw EOFException();
    }

    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
    input[0] = toupper(input[0]);

    if (input == "Yes")
    {
      return true;
    }
    else if (input == "No")
    {
      return false;
    }
    else
    {
      std::cerr << "Invalid command." << std::endl;
    }
  }
}

std::string ConcreteTextViewController::playerColourEnumToString(PlayerColour colour)
{
  std::string returnColour;

  switch (colour)
  {
  case PlayerColour::BLUE:
    returnColour = "Blue";
    break;
  case PlayerColour::RED:
    returnColour = "Red";
    break;
  case PlayerColour::YELLOW:
    returnColour = "Yellow";
    break;
  case PlayerColour::ORANGE:
    returnColour = "Orange";
    break;
  default:
    //doNothing
    break;
  }

  return returnColour;
}

std::string ConcreteTextViewController::resourceTypeEnumToString(ResourceType type)
{

  std::string resType;

  switch (type)
  {
  case ResourceType::BRICK:
    resType = "BRICK";
    break;
  case ResourceType::ENERGY:
    resType = "ENERGY";
    break;
  case ResourceType::GLASS:
    resType = "GLASS";
    break;
  case ResourceType::HEAT:
    resType = "HEAT";
    break;
  case ResourceType::WIFI:
    resType = "WIFI";
    break;
  case ResourceType::PARK:
    resType = "PARK";
    break;
  default:
    //doNothing
    break;
  }
  return resType;
}

std::vector<std::string> ConcreteTextViewController::getDuringTurnInput() const
{
  cin.exceptions(ios::eofbit);

  while (true)
  {

    std::cout << "What would you like to do? (Type \"help\" for list of commands)" << std::endl;

    std::string identifier;

    try
    {
      std::cout << "> ";
      std::cin >> identifier;
    }
    catch (std::ios::failure e)
    {
      throw EOFException();
    }

    std::transform(identifier.begin(), identifier.end(), identifier.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
    std::vector<std::string> result;

    if (identifier == "board")
    {
      result.push_back("board");
      return result;
    }
    else if (identifier == "status")
    {
      result.push_back("status");
      return result;
    }
    else if (identifier == "residences")
    {
      result.push_back("residences");
      return result;
    }
    else if (identifier == "build-road")
    {

      result.push_back("build-road");

      string temp;
      int roadNum;

      try
      {
        std::cin >> temp;
        roadNum = stoi(temp);
      }
      catch (ios::failure &e)
      {
        throw EOFException();
      }
      catch (invalid_argument &e)
      {
        std::cerr << "Invalid command. " << temp << " is not a valid integer."
                  << " Please enter a valid integer." << std::endl;
        continue;
      }

      if (roadNum < 0)
      {
        std::cerr << temp << " is not a valid integer. Please enter a valid integer." << std::endl;
        continue;
      }

      result.push_back(std::to_string(roadNum));

      return result;
    }
    else if (identifier == "build-res")
    {
      result.push_back("build-res");

      string temp;
      int housingNum;

      try
      {
        std::cin >> temp;
        housingNum = stoi(temp);
      }
      catch (ios::failure &e)
      {
        throw EOFException();
      }
      catch (invalid_argument &e)
      {
        std::cerr << "Invalid command. " << temp << " is not a valid integer."
                  << " Please enter a valid integer." << std::endl;
        continue;
      }

      if (housingNum < 0)
      {
        std::cerr << temp << " is not a valid integer. Please enter a valid integer." << std::endl;
        continue;
      }

      result.push_back(std::to_string(housingNum));

      return result;
    }
    else if (identifier == "improve")
    {
      result.push_back("improve");

      string temp;
      int housingNum;

      try
      {
        std::cin >> temp;
        housingNum = stoi(temp);
      }
      catch (ios::failure &e)
      {
        throw EOFException();
      }
      catch (invalid_argument &e)
      {
        std::cerr << "Invalid command. " << temp << " is not a valid integer."
                  << " Please enter a valid integer." << std::endl;
        continue;
      }

      if (housingNum < 0)
      {
        std::cerr << temp << " is not a valid integer. Please enter a valid integer." << std::endl;
        continue;
      }

      result.push_back(std::to_string(housingNum));

      return result;
    }
    else if (identifier == "trade")
    {
      result.push_back("trade");

      std::string colour;

      std::string give;

      std::string take;

      while (true)
      {
        try
        {
          std::cin >> colour;
          std::transform(colour.begin(), colour.end(), colour.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
          colour[0] = toupper(colour[0]);
        }
        catch (std::ios::failure e)
        {
          throw EOFException();
        }

        if (colour != "Blue" && colour != "Red" && colour != "Orange" && colour != "Yellow")
        {
          std::cerr << "Invalid command. Please enter trade info again. (-colour -resourceGive -resourceRecieve)" << std::endl;
          continue;
        }

        try
        {
          std::cin >> give;
          std::transform(give.begin(), give.end(), give.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
          give[0] = toupper(give[0]);
        }
        catch (std::ios::failure e)
        {
          throw EOFException();
        }

        if (give != "Brick" && give != "Energy" && give != "Glass" && give != "Heat" && give != "Wifi")
        {
          std::cerr << "Invalid item. Please enter resource again." << std::endl;
          continue;
        }

        try
        {
          std::cin >> take;
          std::transform(take.begin(), take.end(), take.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
          take[0] = toupper(take[0]);
        }
        catch (std::ios::failure e)
        {
          throw EOFException();
        }

        if (take != "Brick" && take != "Energy" && take != "Glass" && take != "Heat" && take != "Wifi")
        {
          std::cerr << "Invalid item. Please enter resource again." << std::endl;
          continue;
        }

        result.push_back(colour);
        result.push_back(give);
        result.push_back(take);
        return result;
      }
    }
    else if (identifier == "next")
    {
      result.push_back("next");
      return result;
    }
    else if (identifier == "save")
    {
      result.push_back("save");

      std::string file;

      try
      {
        std::cin >> file;
      }
      catch (std::ios::failure e)
      {
        throw EOFException();
      }

      result.push_back(file);

      return result;
    }
    else if (identifier == "help")
    {
      result.push_back("help");
      return result;
    }
    else
    {
      std::cerr << "Invalid command." << std::endl;
    }
  }
}

void ConcreteTextViewController::printGeeseMessage(Player &loser, int numRemoval) const
{
  std::cout << "Builder " << playerColourEnumToString(loser.colour) << " loses " << numRemoval << " resources to the geese. They lose:" << std::endl;
}

void ConcreteTextViewController::printGeeseLostResources(int numResource, ResourceType resourceName) const
{
  std::cout << numResource << " " << resourceTypeEnumToString(resourceName) << std::endl;
}

void ConcreteTextViewController::printRobPlayer(Player &robber, ResourceType resource, Player &victim) const
{
  std::cout << "Builder " << playerColourEnumToString(robber.colour) << " steals " << resourceTypeEnumToString(resource) << " from builder " << playerColourEnumToString(victim.colour) << std::endl;
}

void ConcreteTextViewController::printStatus() const
{
  for (auto &player : game->players)
  {
    std::cout << playerColourEnumToString(player->colour) << " has " << player->status.getBuildingPoints() << " building points, " << player->status.numBricks << " BRICK, "
              << player->status.numEnergies << " ENERGY, " << player->status.numGlass << " GLASS, " << player->status.numHeat << " HEAT, " << player->status.numWifi << " WIFI." << std::endl;
  }
}

void ConcreteTextViewController::printResidences(const Player &player) const
{
  std::cout << playerColourEnumToString(player.colour) << " has built:" << std::endl;

  for (auto residence : player.getResidences())
  {
    if (residence->type == VertexType::BASEMENT)
    {
      cout << residence->location << " B" << std::endl;
    }
    else if (residence->type == VertexType::HOUSE)
    {
      cout << residence->location << " H" << std::endl;
    }
    else
    {
      cout << residence->location << " T" << std::endl;
    }
  }
}

int ConcreteTextViewController::getInitialBuildResidenceLocation(const Player &player) const
{
  cin.exceptions(ios::eofbit);
  while (true)
  {
    std::cout << "Builder " << playerColourEnumToString(player.colour) << " where do you want to build a basement?" << std::endl;
    std::cout << "> ";
    string temp;
    int location;

    try
    {
      std::cin >> temp;
      location = stoi(temp);
      return location;
    }
    catch (ios::failure &e)
    {
      throw EOFException();
    }
    catch (invalid_argument &e)
    {
      std::cerr << "Invalid command. Please enter a valid integer." << std::endl;
      continue;
    }
  }
}

void ConcreteTextViewController::printError(const exception &e) const
{
  std::cerr << "ERROR: " << e.what() << std::endl;
}

int ConcreteTextViewController::getLoadedDiceInput() const
{
  cin.exceptions(ios::eofbit);
  while (true)
  {
    std::cout << "Input a roll between 2 and 12:" << std::endl;
    std::cout << "> ";
    string temp;
    int roll;

    try
    {
      std::cin >> temp;
      roll = stoi(temp);

      if (roll < 2 || roll > 12)
      {
        std::cerr << "Invalid number." << std::endl;
        continue;
      }

      return roll;
    }
    catch (ios::failure &e)
    {
      throw EOFException();
    }
    catch (invalid_argument &e)
    {
      std::cerr << "Invalid command. Please enter a valid integer." << std::endl;
      continue;
    }
  }
}

void ConcreteTextViewController::printRollAmt(int rollAmt) const
{
  std::cout << "A " << rollAmt << " was rolled" << std::endl;
}

void ConcreteTextViewController::printRollDiceHelp() const
{
  std::cout << "Valid commands:" << std::endl;
  std::cout << "~ load : changes current builder's dice type to 'loaded'" << std::endl;
  std::cout << "~ fair : changes current builder's dice type to 'fair'" << std::endl;
  std::cout << "~ roll : rolls the dice and distributes resources" << std::endl;
  std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3. " << std::endl;
  std::cout << "~ help : prints out the list of commands." << std::endl;
}

void ConcreteTextViewController::printHelp() const
{
  std::cout << "Valid commands:" << std::endl;
  std::cout << "~ board" << std::endl;
  std::cout << "~ status" << std::endl;
  std::cout << "~ residences" << std::endl;
  std::cout << "~ build-road <edge#>" << std::endl;
  std::cout << "~ build-res <housing#>" << std::endl;
  std::cout << "~ improve <housing#>" << std::endl;
  std::cout << "~ trade <colour> <give> <take>" << std::endl;
  std::cout << "~ next" << std::endl;
  std::cout << "~ save <file>" << std::endl;
  std::cout << "~ help" << std::endl;
}

void ConcreteTextViewController::printResults() const
{
  bool gaveAnyResources = false;
  for (auto &player : game->players)
  {
    if (player->status.queueBricks || player->status.queueEnergies || player->status.queueGlass || player->status.queueHeat || player->status.queueWifi)
    {
      std::cout << "Builder " << playerColourEnumToString(player->colour) << " gained:" << std::endl;
      gaveAnyResources = true;
    }

    if (player->status.queueBricks)
    {
      std::cout << player->status.queueBricks << " BRICK" << std::endl;
    }

    if (player->status.queueEnergies)
    {
      std::cout << player->status.queueEnergies << " ENERGY" << std::endl;
    }

    if (player->status.queueGlass)
    {
      std::cout << player->status.queueGlass << " GLASS" << std::endl;
    }

    if (player->status.queueHeat)
    {
      std::cout << player->status.queueHeat << " HEAT" << std::endl;
    }

    if (player->status.queueWifi)
    {
      std::cout << player->status.queueWifi << " WIFI" << std::endl;
    }
  }

  if (!gaveAnyResources)
  {
    std::cout << "No builders gained resources." << std::endl;
  }
}

int ConcreteTextViewController::getNewGooseLocation() const
{
  cin.exceptions(ios::eofbit);
  while (true)
  {
    std::cout << "Choose where to place the GEESE." << std::endl;
    std::cout << "> ";
    string temp;
    int location;

    try
    {
      std::cin >> temp;
      location = stoi(temp);
      if(location < 0 || location > 18){
        std::cerr << "Invalid goose location" << std::endl;
        continue;
      }else{
        return location;
      }
      
    }
    catch (ios::failure &e)
    {
      throw EOFException();
    }
    catch (invalid_argument &e)
    {
      std::cerr << "Invalid command. Please enter a valid integer." << std::endl;
      continue;
    }
  }
}

Player &ConcreteTextViewController::getStealFromWho(std::vector<Player *> options, Player &player) const
{

  while (true)
  {
    std::cout << "Builder " << playerColourEnumToString(player.colour) << " can choose to steal from ";

    for (auto &option : options)
    {
      std::cout << playerColourEnumToString(option->colour);
    }

    std::cout << "." << std::endl;

    //TODO: finish choose builkder to steal from

    std::cout << "Choose a builder to steal from." << std::endl;
    std::cout << "> ";

    std::string colour;

    try
    {
      std::cin >> colour;
      std::transform(colour.begin(), colour.end(), colour.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
      colour[0] = toupper(colour[0]);
    }
    catch (ios::failure &e)
    {
      throw EOFException();
    }

    PlayerColour candidate;

    if (colour == "Blue")
    {
      candidate = PlayerColour::BLUE;
    }
    else if (colour == "Red")
    {
      candidate = PlayerColour::RED;
    }
    else if (colour == "Yellow")
    {
      candidate = PlayerColour::YELLOW;
    }
    else if (colour == "Orange")
    {
      candidate = PlayerColour::ORANGE;
    }
    else
    {
      std::cerr << "Invalid colour, please try again." << std::endl;
    }

    if (std::find_if(options.begin(), options.end(), [candidate](Player *x) -> bool { return x->colour == candidate; }) == options.end())
    {
      std::cerr << "Invalid colour, please try again." << std::endl;
    }
    else
    {
      return **(std::find_if(options.begin(), options.end(), [candidate](Player *x) -> bool { return x->colour == candidate; }));
      break;
    }
  }
}

void ConcreteTextViewController::printNoBuildersToStealFrom(Player &player) const
{
  std::cout << "Builder " << playerColourEnumToString(player.colour) << " has no builders to steal from." << std::endl;
}

void ConcreteTextViewController::printSave(std::string outputFileName) const
{
  std::cout << "Saving to " << outputFileName << "..." << std::endl;
}

void ConcreteTextViewController::printSuccessfulBuilding() const {
  std::cout << "Basement successfully built." << std::endl;
}

void ConcreteTextViewController::printSuccessfulImprovement() const {
  std::cout << "Improvement successfully built." << std::endl;
}

void ConcreteTextViewController::printSuccessfulRoad() const {
  std::cout << "Road successfully built." << std::endl;
}
void ConcreteTextViewController::printWinner(const Player &player) const
{
  std::cout << "Builder " << playerColourEnumToString(player.colour) << " wins!" << std::endl;
}

bool ConcreteTextViewController::getPlayAgain() const
{
  while (true)
  {
    std::cout << "Would you like to play again? (Yes|No)" << std::endl;
    std::cout << "> ";

    std::string response;
    try
    {
      std::cin >> response;
      std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
      response[0] = toupper(response[0]);
    }
    catch (ios::failure &e)
    {
      throw EOFException();
    }

    if (response == "Yes")
    {
      return true;
    }
    else if (response == "No")
    {
      return false;
    }
    else
    {
      std::cerr << "Invalid Input." << std::endl;
      continue;
    }
  }
}
