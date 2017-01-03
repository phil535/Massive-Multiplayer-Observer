#include <iostream>
#include "Game.h"

using std::cout;
using std::endl;

Game::Game()
{ }

Game &Game::instance()
{
  static Game gameSingleton;
  return gameSingleton;
}

int Game::run(const std::vector<const char *> &args)
{
  // todo: start implementation here!

  cout << "Game::run..." << endl;

  return 0;
}