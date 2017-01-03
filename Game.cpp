#include <iostream>
#include <thread>
#include "Game.h"
#include "RandomNumberGenerator.h"

using std::cout;
using std::endl;

Game::Game() : running_(false)
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
  Game::instance().running_ = true;

  // todo: start implementation here!
  Game::instance().setBoardSize();
  cout << "Game::run..." << endl;

  Position max = Game::instance().getBoardSize();
  Position tst = RandomNumberGenerator::instance().getRandomPosition(max);

  cout << "Test-position is [" << tst.getX() << "," << tst.getY() << "]." << endl;

  std::thread update_thread(Game::update);

  for (; Game::instance().running_;)
  {
    std::cout << "> ";
    std::string input_buffer;
    std::getline(std::cin, input_buffer);

    if (input_buffer == "quit")
    {
      Game::instance().running_ = false;
      break;
    }
  }

  update_thread.join();

  return 0;
}

void Game::update()
{
  for (; Game::instance().running_;)
  {
    // update player

    std::this_thread::sleep_for(std::chrono::milliseconds(Game::instance().UPDATE_CYCLE_MS));
  }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Game::setBoardSize(const Position & set_val)
{
  board_size_ = set_val;
}
