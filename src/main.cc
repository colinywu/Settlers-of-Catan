#include "./model/gameModel.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

void usage(std::string programName)
{
  std::cerr << "Usage: " << programName << " -seed xxx -load xxx -board xxx -random-board" << std::endl;
  std::cerr << "Note: the program will only accept situations where arguments \"-load xxx\", \"-board xxx\", and \"-random-board\" occur mutually exclusively" << std::endl;
}

int main(int argc, char const *argv[])
{

  unsigned int seed = 0;

  bool loadSaved = false;
  bool loadBoard = false;
  bool randomBoard = false;

  std::string fileName;
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);

  //create board before player



  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg == "-seed")
    {
      if (i + 1 < argc)
      {
        //converts to integer using stringstream
        std::istringstream nextArg{argv[i + 1]};
        unsigned int test = 0;
        //nextarg goes into test and checks if that succeeded (nextarg was not empty) and if the now updated test is a integer
        if (nextArg >> test)
        {
          seed = test;
          //no need to check what the next argument is because it is definitely a integer!
          i++;
        }
        else
        {
          //not an integer
          usage(argv[0]);
          return 1;
        }
      }
      else
      {
        usage(argv[0]);
        return 1;
      }
    }
    else if (arg == "-load")
    {

      if (loadBoard || randomBoard)
      {

        usage(argv[0]);
        return 1;
      }

      if (i + 1 < argc)
      {

        fileName = argv[i + 1];
        i++;
        loadSaved = true;
      }
      else
      {
        usage(argv[0]);
        return 1;
      }
    }
    else if (arg == "-board")
    {

      if (loadSaved || randomBoard)
      {

        usage(argv[0]);
        return 1;
      }

      if (i + 1 < argc)
      {

        fileName = argv[i + 1];
        loadBoard = true;
        i++;
      }
      else
      {
        usage(argv[0]);
        return 1;
      }
    }
    else if (arg == "-random-board")
    {

      if (loadSaved || loadBoard)
      {

        usage(argv[0]);
        return 1;
      }

      randomBoard = true;
    }
  }

  bool playAgain;
  do
  {
      GameModel gameModel = GameModel{};
    if (loadBoard)
    {
      try
      {
        file.open(fileName);
        gameModel.initializeFromFile(file);
        playAgain = gameModel.runGame(false);
         file.close();
      }
      catch (const std::ifstream::failure &e)
      {
        std::cerr << "Error while reading file" << std::endl;
        return 1;
      }
      catch (std::invalid_argument &e)
      {
        std::cerr << "Something went wrong when loading." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
      }
    }
    else if (loadSaved)
    {
      try
      {

        file.open(fileName);
        gameModel.initializeFromGameState(file);
        playAgain = gameModel.runGame(true);
         file.close();
      }
      catch (const std::ifstream::failure &e)
      {
        std::cerr << "Error while reading file" << std::endl;
        return 1;
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << "Something went wrong when loading." << std::endl;
        std::cerr << error.what() << std::endl;
        return 1;
      }
    }
    else if (randomBoard)
    {
      if (seed)
      {
        gameModel.initialize(seed);
      }
      else
      {
        gameModel.initialize();
      }
      playAgain = gameModel.runGame(false);
    }
    else
    {
      usage(argv[0]);
      return 1;
    }

  } while (playAgain);
}
