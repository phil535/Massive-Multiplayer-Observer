#include <iostream>
#include "Game.h"
#include "RandomNumberGenerator.h"

using std::cout;
using std::endl;

Game::Game()
{}

/*--------------------------------------------------------------------------------------------------------------------*/

Game &Game::instance()
{
  static Game gameSingleton;
  return gameSingleton;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Game::run(const std::vector<const char *> &args)
{
  // todo: start implementation here!
  Game::instance().setBoardSize();
  cout << "Game::run..." << endl;

  Position max = Game::instance().getBoardSize();
  Position tst = RandomNumberGenerator::instance().getRandomPosition(max);

  cout << "Test-position is [" << tst.getX() << "," << tst.getY() << "]." << endl;

  return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Game::setBoardSize(const Position & set_val)
{
  board_size_ = set_val;
}
