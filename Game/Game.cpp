#include <iostream>
#include <thread>
#include <string>
#include "Game.h"
#include "RandomNumberGenerator.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------------------------------*/
Game::Game() : running_(false)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
Game::~Game()
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
  Game::instance().setBoardSize();

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

  // start websocketserver on port 8888
  std::thread websocket_thread(std::bind(&WebsocketServer::run, &Game::instance().websocket_server_, 8888));

  // Add initial players.
  while( init_player_cnt-- )
    Game::instance().addPlayer();

  // start gameloop
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
    else if (input_buffer == "add")
    {
      Game::instance().addPlayer(RandomNumberGenerator::instance().getRandomPosition(Game::instance().getBoardSize()),
                                 RandomNumberGenerator::instance().getRandomDirection());
    }
    else if (input_buffer == "list")
    {
      for (auto &p : Game::instance().players_)
        std::cout << *(p.second) << std::endl;
    }
  }

  Game::instance().players_.clear();

  // stop gameloop
  update_thread.join();

  // stop websocketserver
  Game::instance().websocket_server_.stop();
  websocket_thread.join();

  return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::addPlayer(Position position, Position direction)
{
  std::unique_ptr<Player> new_player(new Player(position.getX(), position.getY(), direction.getX(), direction.getY()));

  players_.insert(std::make_pair(new_player->getId(), std::move(new_player)));

}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::addPlayer(void)
{
  std::unique_ptr<Player> new_player(new Player());

  players_.insert(std::make_pair(new_player->getId(), std::move(new_player)));

}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::removePlayer(size_t id)
{
  players_.erase(id);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::update()
{
  for (; Game::instance().running_;)
  {
    // move players
    for (auto &p : Game::instance().players_)
      (p.second)->move();

    // update current state
    Game::instance().websocket_server_.broadcastMessage(Game::instance().getJsonPlayerState());

    std::this_thread::sleep_for(std::chrono::milliseconds(Game::instance().UPDATE_CYCLE_MS));
  }
}
/*--------------------------------------------------------------------------------------------------------------------*/
std::string Game::getJsonPlayerState() const
{
  std::stringstream ss;

  ss << "{\"players\":[";

  for(auto p = Game::instance().players_.begin(); p != Game::instance().players_.end();p++)
  {
    if(p != Game::instance().players_.begin())
      ss << ", ";

    ss << "{\"id\": " << p->second->getId()
    << ",\"x\": " << p->second->getPosition().getX()
    << ",\"y\": " << p->second->getPosition().getY() << "}";
  }
  ss << "]}";
  return ss.str();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::setBoardSize(const Position set_val)
{
  board_size_ = set_val;
}
