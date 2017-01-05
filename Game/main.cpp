#include <iostream>
#include <vector>

#include "Game.h"

int main(int argc, char *argv[])
{
  try
  {
    const std::vector<std::string> args(argv + 1, argv + argc);
    Game game;
    return game.run(args);
  }
  catch (std::exception &ex)
  {
    std::cout << ex.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknow exception was caught!" << std::endl;
  }
  return -1;
}