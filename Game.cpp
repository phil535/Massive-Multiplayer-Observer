#include <iostream>
#include <thread>
#include <string>
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

  for( std::vector<const char *>::const_iterator itr = args.begin(); itr != args.end(); ++itr )
  {
    if(std::string(*itr) == "--boardsize")
    {
      if((itr + 1) != args.end())
      {
        int board_width, board_height;
        try
        {
          std::string tmp_string_width = std::string(*(itr + 1));
          board_width = std::stoi(tmp_string_width);
          itr++;

          if((itr + 1) != args.end())
          {
            try
            {
              std::string tmp_string_height = std::string(*(itr + 1));
              board_height = std::stoi(tmp_string_height);
              Game::instance().setBoardSize(Position(board_width, board_height));
              itr++;
              continue;
            }
            catch (std::exception & e)
            {}
          }
          Game::instance().setBoardSize(Position(board_width, board_width));
          continue;
        }
        catch (std::exception & e)
        {}

      }
    }
  }

  cout << "Game::run..." << endl;

  Position tst = RandomNumberGenerator::instance().getRandomPosition(Game::instance().getBoardSize());

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

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::addPlayer(Position position, Position direction)
{
  std::unique_ptr<Player> new_player(new Player(position.getX(), position.getY(), direction.getX(), direction.getY()));

  players_.insert(std::make_pair(new_player->getId(), std::move(new_player)));

}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::removePlayer(size_t id)
{
  players_.erase(id);
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

void Game::setBoardSize(const Position set_val)
{
  board_size_ = set_val;
}
