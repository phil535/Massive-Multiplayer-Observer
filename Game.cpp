#include <iostream>
#include <string>
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

  return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Game::setBoardSize(const Position set_val)
{
  board_size_ = set_val;
}
