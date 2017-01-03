#include <iostream>
#include <vector>

#include "Game.h"

int main(int argc, char *argv[])
{
  try
  {
    const std::vector<const char *> args(argv, argv + argc);
    return Game::instance().run(args);
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