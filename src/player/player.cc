#include "player.h"
#include <exception>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <stdexcept>
using namespace std;

std::string Player::playerColourEnumToString(PlayerColour colour) {
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

Player::Player(Board *board, PlayerColour colour, GameViewController *gameViewController) : board{board}, colour{colour}, gameViewController{gameViewController}
{
    status = Status{}; //here
    dice = std::make_unique<ConcreteLoadedDice>(gameViewController, board->seed);
}

Player::Player(Board *board, PlayerColour colour, GameViewController *gameViewController, Status status) : board{board}, colour{colour}, gameViewController{gameViewController}, status{status} {
    dice = std::make_unique<ConcreteLoadedDice>(gameViewController, board->seed);
}

void Player::throwErrorifNohasResource(Player &trader, Player &recipient, const ResourceType give, const ResourceType receive) {
    bool invalidTrader = false;
    bool invalidRecipient = false;
    stringstream ss;

    if (give == ResourceType::BRICK && receive == ResourceType::BRICK) {
        ss << "Cannot trade for the same resouce." << std::endl; 
        throw invalid_argument{ss.str()};
    }
    else if (give == ResourceType::BRICK && receive == ResourceType::ENERGY)
    {
        if (trader.status.numBricks < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numEnergies < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::BRICK && receive == ResourceType::GLASS)
    {
        if (trader.status.numBricks < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numGlass < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::BRICK && receive == ResourceType::HEAT)
    {
        if (trader.status.numBricks < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numHeat < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::BRICK && receive == ResourceType::WIFI)
    {
        if (trader.status.numBricks < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numWifi < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::ENERGY && receive == ResourceType::BRICK)
    {
        if (trader.status.numEnergies < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numBricks < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICKS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICKS." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::ENERGY && receive == ResourceType::ENERGY)
    {
        ss << "Cannot trade for the same resouce." << std::endl; 
        throw invalid_argument{ss.str()};
    }
    else if (give == ResourceType::ENERGY && receive == ResourceType::GLASS)
    {
        if (trader.status.numEnergies < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numGlass < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::ENERGY && receive == ResourceType::HEAT)
    {
        if (trader.status.numEnergies < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numHeat < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::ENERGY && receive == ResourceType::WIFI)
    {
        if (trader.status.numEnergies < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numWifi < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::GLASS && receive == ResourceType::BRICK)
    {
        if (trader.status.numGlass < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numBricks < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::GLASS && receive == ResourceType::ENERGY)
    {
        if (trader.status.numGlass < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numEnergies < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::GLASS && receive == ResourceType::GLASS)
    {
        ss << "Cannot trade for the same resouce."<< std::endl; 
        throw invalid_argument{ss.str()};
    }
    else if (give == ResourceType::GLASS && receive == ResourceType::HEAT)
    {
        if (trader.status.numGlass < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numHeat < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::GLASS && receive == ResourceType::WIFI)
    {
        if (trader.status.numGlass < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numWifi < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::HEAT && receive == ResourceType::BRICK)
    {
        if (trader.status.numHeat < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numBricks < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::HEAT && receive == ResourceType::ENERGY)
    {
        if (trader.status.numHeat < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numEnergies < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::HEAT && receive == ResourceType::GLASS)
    {
        if (trader.status.numHeat < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numGlass < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::HEAT && receive == ResourceType::HEAT)
    {
        ss << "Cannot trade for the same resouce."<< std::endl; 
        throw invalid_argument{ss.str()};
    }
    else if (give == ResourceType::HEAT && receive == ResourceType::WIFI)
    {
        if (trader.status.numHeat < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numWifi < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::WIFI && receive == ResourceType::BRICK)
    {
        if (trader.status.numWifi < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numBricks < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough BRICK." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::WIFI && receive == ResourceType::ENERGY)
    {
        if (trader.status.numWifi < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numEnergies < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough ENERGY." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::WIFI && receive == ResourceType::GLASS)
    {
        if (trader.status.numWifi < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numGlass < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough GLASS." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::WIFI && receive == ResourceType::HEAT)
    {
        if (trader.status.numWifi < 1)
        {
            invalidTrader = true;
        }

        if (recipient.status.numHeat < 1)
        {
            invalidRecipient = true;
        }

        if (invalidTrader && invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            ss <<  "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidTrader) {
            ss << "Builder " << playerColourEnumToString(trader.colour) << " does not have enough WIFI." << std::endl;
            throw invalid_argument{ss.str()};
        }

        if (invalidRecipient) {
            ss << "Builder " << playerColourEnumToString(recipient.colour) << " does not have enough HEAT." << std::endl;
            throw invalid_argument{ss.str()};
        }
    }
    else if (give == ResourceType::WIFI && receive == ResourceType::WIFI)
    {
        ss << "Cannot trade for the same resouce."<< std::endl; 
        throw invalid_argument{ss.str()};
    }
}

void Player::proposeTrade(Player &recipient, const ResourceType give, const ResourceType receive) {

    if (&recipient == this) {
        throw invalid_argument{"Cannot trade with yourself."};
    }

    try {
        throwErrorifNohasResource(*this, recipient, give, receive);
    } catch (invalid_argument e) {
        throw e;
    }
   
    // give + receive vs. proposorType + proposedType
    if (recipient.respondTrade(*this, receive, give))
    {
        if (receive == ResourceType::BRICK)
        {
            if (give == ResourceType::ENERGY)
            {
                this->status.numEnergies -= 1;
                this->status.numBricks += 1;

                recipient.status.numEnergies += 1;
                recipient.status.numBricks -= 1;
            }
            else if (give == ResourceType::HEAT)
            {
                this->status.numHeat -= 1;
                this->status.numBricks += 1;

                recipient.status.numHeat += 1;
                recipient.status.numBricks -= 1;
            }
            else if (give == ResourceType::BRICK)
            {
                this->status.numBricks -= 1;
                this->status.numBricks += 1;

                recipient.status.numBricks += 1;
                recipient.status.numBricks -= 1;
            }
            else if (give == ResourceType::WIFI)
            {
                this->status.numWifi -= 1;
                this->status.numBricks += 1;

                recipient.status.numWifi += 1;
                recipient.status.numBricks -= 1;
            }
            else if (give == ResourceType::GLASS)
            {
                this->status.numGlass -= 1;
                this->status.numBricks += 1;

                recipient.status.numGlass += 1;
                recipient.status.numBricks -= 1;
            }
        }
        else if (receive == ResourceType::ENERGY)
        {
            if (give == ResourceType::ENERGY)
            {
                this->status.numEnergies -= 1;
                this->status.numEnergies += 1;

                recipient.status.numEnergies += 1;
                recipient.status.numEnergies -= 1;
            }
            else if (give == ResourceType::HEAT)
            {
                this->status.numEnergies -= 1;
                this->status.numEnergies += 1;

                recipient.status.numEnergies += 1;
                recipient.status.numEnergies -= 1;
            }
            else if (give == ResourceType::BRICK)
            {
                this->status.numBricks -= 1;
                this->status.numEnergies += 1;

                recipient.status.numBricks += 1;
                recipient.status.numEnergies -= 1;
            }
            else if (give == ResourceType::WIFI)
            {
                this->status.numWifi -= 1;
                this->status.numEnergies += 1;

                recipient.status.numWifi += 1;
                recipient.status.numEnergies -= 1;
            }
            else if (give == ResourceType::GLASS)
            {
                this->status.numGlass -= 1;
                this->status.numEnergies += 1;

                recipient.status.numGlass += 1;
                recipient.status.numEnergies -= 1;
            }
        }
        else if (receive == ResourceType::HEAT)
        {
            if (give == ResourceType::ENERGY)
            {
                this->status.numHeat += 1;
                this->status.numEnergies -= 1;

                recipient.status.numHeat -= 1;
                recipient.status.numEnergies += 1;
            }
            else if (give == ResourceType::HEAT)
            {
                this->status.numHeat += 1;
                this->status.numHeat -= 1;

                recipient.status.numHeat -= 1;
                recipient.status.numHeat += 1;
            }
            else if (give == ResourceType::BRICK)
            {
                this->status.numHeat += 1;
                this->status.numBricks -= 1;

                recipient.status.numHeat -= 1;
                recipient.status.numBricks += 1;
            }
            else if (give == ResourceType::WIFI)
            {
                this->status.numHeat += 1;
                this->status.numWifi -= 1;

                recipient.status.numHeat -= 1;
                recipient.status.numWifi += 1;
            }
            else if (give == ResourceType::GLASS)
            {
                this->status.numHeat += 1;
                this->status.numGlass -= 1;

                recipient.status.numHeat -= 1;
                recipient.status.numGlass += 1;
            }
        }
        else if (receive == ResourceType::WIFI)
        {
            if (give == ResourceType::ENERGY)
            {
                this->status.numWifi += 1;
                this->status.numEnergies -= 1;

                recipient.status.numWifi -= 1;
                recipient.status.numEnergies += 1;
            }
            else if (give == ResourceType::HEAT)
            {
                this->status.numWifi += 1;
                this->status.numHeat -= 1;

                recipient.status.numWifi -= 1;
                recipient.status.numHeat += 1;
            }
            else if (give == ResourceType::BRICK)
            {
                this->status.numWifi += 1;
                this->status.numBricks -= 1;

                recipient.status.numWifi -= 1;
                recipient.status.numBricks += 1;
            }
            else if (give == ResourceType::WIFI)
            {
                this->status.numWifi += 1;
                this->status.numWifi -= 1;

                recipient.status.numWifi -= 1;
                recipient.status.numWifi += 1;
            }
            else if (give == ResourceType::GLASS)
            {
                this->status.numWifi += 1;
                this->status.numGlass -= 1;

                recipient.status.numWifi -= 1;
                recipient.status.numGlass += 1;
            }
        }
        else if (receive == ResourceType::GLASS)
        {
            if (give == ResourceType::ENERGY)
            {
                this->status.numGlass += 1;
                this->status.numEnergies -= 1;

                recipient.status.numGlass -= 1;
                recipient.status.numEnergies += 1;
            }
            else if (give == ResourceType::HEAT)
            {
                this->status.numGlass += 1;
                this->status.numHeat -= 1;

                recipient.status.numGlass -= 1;
                recipient.status.numHeat += 1;
            }
            else if (give == ResourceType::BRICK)
            {
                this->status.numGlass += 1;
                this->status.numBricks -= 1;

                recipient.status.numGlass -= 1;
                recipient.status.numBricks += 1;
            }
            else if (give == ResourceType::WIFI)
            {
                this->status.numGlass += 1;
                this->status.numWifi -= 1;

                recipient.status.numGlass -= 1;
                recipient.status.numWifi += 1;
            }
            else if (give == ResourceType::GLASS)
            {
                this->status.numGlass += 1;
                this->status.numGlass -= 1;

                recipient.status.numGlass -= 1;
                recipient.status.numGlass += 1;
            }
        }
    }
    else
    {
        return;
    }
}

bool Player::respondTrade(Player &trader, const ResourceType give, const ResourceType receive) {
    return gameViewController->getTradeInput(trader, *this, receive, give);
}

vector<Vertex *> Player::getResidences() const
{
    vector<Vertex *> residences;

    for (auto &residence : board->vertices)
    {
        if (residence->checkOwner() == this)
        {
            residences.push_back(residence.get());
        }
    }
    return residences;
}

void Player::buildRoad(const int location)
{
    try
    {
        board->addRoad(location, *this);
    }
    catch (invalid_argument  & e)
    {
        throw;
    }

    gameViewController->printSuccessfulRoad();
}

void Player::buildResidence(const int location, bool isNewGame)
{
    //check if can build. Board should do the other checks (if road, if adjacent)
    try
    {
        board->addResidence(location, *this, isNewGame);
    }
    catch (invalid_argument & e)
    {
        throw;
    }
    
    gameViewController->printSuccessfulBuilding();
}

void Player::improveResidence(const int location)
{
    try
    {
        board->improveResidence(location, *this);
    }
    catch (invalid_argument & e)
    {
        throw;
    }

    gameViewController->printSuccessfulImprovement();
}

void Player::tryRobbedByGoose()
{
    //see if over 10, if yes, randomly take away half
    if (moreThanTenCards())
    {
        int numCards = status.getTotalNumResource();
        int numRemoval = floor(numCards / 2);

        int lostBricks = 0;
        int lostEnergies = 0;
        int lostGlass = 0;
        int lostHeat = 0;
        int lostWifi = 0;

        gameViewController->printGeeseMessage(*this, numRemoval);

        for (int i = 0; i < numRemoval; i++)
        {
            int remove = rand() % numCards + 1;

            if ((remove - status.numBricks) <= 0)
            {
                status.numBricks -= 1;
                lostBricks += 1;
                numCards -= 1;
                continue; //is this right?
            }

            remove -= status.numBricks;

            if ((remove - status.numEnergies) <= 0)
            {
                status.numEnergies -= 1;
                lostEnergies += 1;
                numCards -= 1;
                continue;
            }

            remove -= status.numEnergies;

            if ((remove - status.numGlass) <= 0)
            {
                status.numGlass -= 1;
                lostGlass += 1;
                numCards -= 1;
                continue;
            }

            remove -= status.numGlass;

            if ((remove - status.numHeat) <= 0)
            {
                status.numHeat -= 1;
                lostHeat += 1;
                numCards -= 1;
                continue;
            }

            remove -= status.numHeat;

            if ((remove - status.numWifi) <= 0)
            {
                status.numWifi -= 1;
                lostWifi += 1;
                numCards -= 1;
                continue;
            }
        }

        if (lostBricks > 0)
        {
            gameViewController->printGeeseLostResources(lostBricks, ResourceType::BRICK);
        }

        if (lostEnergies > 0)
        {
            gameViewController->printGeeseLostResources(lostEnergies, ResourceType::ENERGY);
        }

        if (lostGlass > 0)
        {
            gameViewController->printGeeseLostResources(lostGlass, ResourceType::GLASS);
        }

        if (lostHeat > 0)
        {
            gameViewController->printGeeseLostResources(lostHeat, ResourceType::HEAT);
        }

        if (lostWifi > 0)
        {
            gameViewController->printGeeseLostResources(lostWifi, ResourceType::WIFI);
        }
    }
}

void Player::robPlayer(Player &victim) {
    //randomly steal 1 resource from victim to THIS
    int remove = rand() % victim.status.getTotalNumResource() + 1;

    if ((remove - victim.status.numBricks) <= 0)
    {
        victim.status.numBricks -= 1;
        this->status.numBricks += 1;
        gameViewController->printRobPlayer(*this, ResourceType::BRICK, victim);
        return;
    }

    remove -= victim.status.numBricks;

    if ((remove - victim.status.numEnergies) <= 0)
    {
        victim.status.numEnergies -= 1;
        this->status.numEnergies += 1;
        gameViewController->printRobPlayer(*this, ResourceType::ENERGY, victim);
        return;
    }

    remove -= victim.status.numEnergies;

    if ((remove - victim.status.numGlass) <= 0)
    {
        victim.status.numGlass -= 1;
        this->status.numGlass += 1;
        gameViewController->printRobPlayer(*this, ResourceType::GLASS, victim);
        return;
    }

    remove -= victim.status.numGlass;

    if ((remove - victim.status.numHeat) <= 0)
    {
        victim.status.numHeat -= 1;
        this->status.numHeat += 1;
        gameViewController->printRobPlayer(*this, ResourceType::HEAT, victim);
        return;
    }

    remove -= victim.status.numHeat;

    if ((remove - victim.status.numWifi) <= 0)
    {
        victim.status.numWifi -= 1;
        this->status.numWifi += 1;
        gameViewController->printRobPlayer(*this, ResourceType::WIFI, victim);
        return;
    }
}

bool Player::moreThanTenCards() const
{
    return (status.getTotalNumResource() >= 10);
}

std::string Player::getSerializedStatus() const
{
    stringstream resources;
    stringstream roads;
    stringstream buildings;
    stringstream out;

    resources << to_string(status.numBricks) << " " + to_string(status.numEnergies) << " " + to_string(status.numGlass) << " " + to_string(status.numHeat) << " " << to_string(status.numWifi) << " ";
    roads << "r ";

    for (auto const &road : status.ownedRoads)
    {
        roads << road.first << " ";
    }

    buildings << "h";
    for (auto const &building : status.ownedBuildings)
    {
        if (building.second->type == VertexType::BASEMENT)
        {
            buildings << " " << building.first << " B";
        }
        else if (building.second->type == VertexType::HOUSE)
        {
            buildings << " " << building.first << " H";
        }
        else
        {
            buildings << " " << building.first << " T";
        }
    }

    out << resources.str() << roads.str() << buildings.str();
    return out.str();
}
