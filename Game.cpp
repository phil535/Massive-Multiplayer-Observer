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

  int init_player_cnt = 0;

  for( std::vector<const char *>::const_iterator itr = args.begin(); itr != args.end(); ++itr )
  {
    if(std::string(*itr) == "--boardsize")
    {
      if ((itr + 1) != args.end())
      {
        int board_width, board_height;
        try
        {
          std::string tmp_string_width = std::string(*(itr + 1));
          board_width = std::stoi(tmp_string_width);
          itr++;

          if ((itr + 1) != args.end())
          {
            try
            {
              std::string tmp_string_height = std::string(*(itr + 1));
              board_height = std::stoi(tmp_string_height);
              Game::instance().setBoardSize(Position(board_width, board_height));
              itr++;
              continue;
            }
            catch (std::exception &e)
            {}
          }
          Game::instance().setBoardSize(Position(board_width, board_width));
          continue;
        }
        catch (std::exception &e)
        {}

      }
    }
    else if(std::string(*itr) == "--init-players")
    {
      if ((itr + 1) != args.end())
      {
        try
        {
          std::string tmp_string_player_cnt = std::string(*(itr + 1));
          init_player_cnt = std::stoi(tmp_string_player_cnt);
          itr++;
          continue;
        }
        catch (std::exception &e)
        {}
      }
    }
  }

  cout << "Game::run..." << endl;

  while( init_player_cnt-- )
  {
  }

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
