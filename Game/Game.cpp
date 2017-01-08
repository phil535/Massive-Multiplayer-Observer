#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <thread>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


#include "Game.h"
#include "MovementPattern.h"


using std::cout;
using std::endl;
using std::mutex;
using std::lock_guard;

const Size Game::BOARD_SIZE = Size(800, 800);


/*--------------------------------------------------------------------------------------------------------------------*/
Game::Game(void) : running_(false)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
Game::~Game(void)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
int Game::run(const std::vector<std::string> &args)
{
  running_ = true;

  // start websocketserver on port 8888
  std::thread websocket_thread(std::bind(&WebsocketServer::run, &websocket_server_, 8888));

  auto it = args.end();
  if((it = std::find(args.begin(), args.end(), "--init-players")) != args.end() && (++it != args.end()))
  {
    try
    {
      auto init_player_count = std::stoi(*it);

      // Add initial players.
      while(init_player_count--) addPlayer();
    }
    catch(...){}
  }

  // start gameloop
  std::thread update_thread(std::bind(&Game::update, this));

  for (;running_;)
  {
    cout << "> ";
    std::string input_buffer;
    std::getline(std::cin, input_buffer);

    std::vector<std::string> cmd_parameters;
    boost::split(cmd_parameters, input_buffer, boost::is_any_of(" \t\r\n"));

    // split into command and parameters
    std::string command(cmd_parameters.front());
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    cmd_parameters.erase(cmd_parameters.begin());

    if(command == "add")
    {
      int player_count = 1;
      std::string strategy;

      try
      {
        player_count = std::stoul(cmd_parameters.at(0));
        strategy = cmd_parameters.at(1);
      }catch(...){}

      for (; player_count--;)
      {
        lock_guard<mutex> lock(mutex_players_);
        auto &new_player = addPlayer();

        if(strategy.length() == 0){}
        else if(strategy == "linear")
        {
          new_player.setStrategy(new LinearMovementPattern(RandomNumberGenerator::instance().getRandomDirection()));
        }
        else if(strategy == "harmonic")
        {
          new_player.setStrategy(new HarmonicMovementPattern(RandomNumberGenerator::instance().getRandomDirection()));
        }
        else if(strategy == "circular")
        {
          new_player.setStrategy(new CircularMovementPattern);
        }
        else
        {
          cout << "usage: add [#] [linear,harmonic,circular]" << endl;
          break;
        }
        cout << "New " << new_player << endl;
      }
    }
    else if(command == "remove")
    {
      lock_guard<mutex> lock(mutex_players_);
      removeAllPlayers();
    }
    else if (command == "list")
    {
      lock_guard<mutex> lock(mutex_players_);

      if(players_.size() == 0)
        cout << "No players in game." << endl;

      for (auto &p : players_)
        cout << *(p.second) << endl;
    }
    else if(command == "test")
    {
      unsigned long test_number = 0;
      try{test_number = std::stoul(cmd_parameters.at(0));}catch(...){}

      switch(test_number)
      {
        case 1:
        {
          lock_guard<mutex> lock(mutex_players_);
          removeAllPlayers();
          addPlayer({400,400}, new IdleMovementPattern);
          addPlayer({200,400}, new LinearMovementPattern({1,0}));
          break;
        }
        case 2:
        {
          lock_guard<mutex> lock(mutex_players_);
          removeAllPlayers();
          addPlayer({0,0}, new LinearMovementPattern({1,1}));
          addPlayer({799,0}, new LinearMovementPattern({-1,1}));
          addPlayer({799,799}, new LinearMovementPattern({-1,-1}));
          addPlayer({0,799}, new LinearMovementPattern({1,-1}));
          break;
        }
        case 3:
        {
          {
            lock_guard<mutex> lock(mutex_players_);
            removeAllPlayers();
          }
          for(int i = 0; i < 6; i++)
          {
            {
              lock_guard<mutex> lock(mutex_players_);
              addPlayer({550, 400}, new CircularMovementPattern);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
          }
          break;
        }
        case 4:
        {
          {
            lock_guard<mutex> lock(mutex_players_);
            removeAllPlayers();
            addPlayer({50, 400}, new HarmonicMovementPattern({1,0}));
            addPlayer({50, 400}, new HarmonicMovementPattern({1,0}));
          }
          break;
        }
        default:
        {
          cout << "usage: test [1-2]" << endl;
          break;
        }
      }
    }
    else if(command == "debug")
    {
      lock_guard<mutex> lock(mutex_players_);

      if(players_.size() == 0)
        cout << "No players in game." << endl;

      for (auto &p : players_)
      {
        auto &player = *(p.second);
        cout << "Player[" << player.getId() << "]: Observers: [";
        for(auto o : player.getObservers())
        {
          if(o != *player.getObservers().begin())
            cout << ", ";
          cout << o->getPlayer().getId();
        }
        cout << "]" << endl;
      }
    }
    else if(command == "quit")
    {
      running_ = false;
      break;
    }
    else
    {
      cout << "Unknown command." << endl;
    }
  }

  {
    lock_guard<mutex> lock(mutex_players_);
    players_.clear();
  }

  // stop gameloop
  update_thread.join();

  // stop websocketserver
  websocket_server_.stop();
  websocket_thread.join();

  return 0;
}

Player &Game::addPlayer(Position position, MovementPattern *strategy)
{
  std::unique_ptr<Player> new_player(new Player(*this, position, strategy));
  size_t id = new_player->getId();
  players_.insert(std::make_pair(new_player->getId(), std::move(new_player)));
  return *(players_[id]);
}
/*--------------------------------------------------------------------------------------------------------------------*/
Player &Game::addPlayer(Position position)
{
  return addPlayer(position, RandomNumberGenerator::instance().getRandomMovementPattern());
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player &Game::addPlayer(void)
{
  return addPlayer(RandomNumberGenerator::instance().getRandomVector({0,0}, BOARD_SIZE - 1));
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::removeAllPlayers()
{
  players_.clear();
  websocket_server_.broadcastMessage(getJsonPlayerState());
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::update()
{
  for (;running_;)
  {
    {
      lock_guard<mutex> lock(mutex_players_);

      // move players
      for (auto &p : players_)
        (p.second)->move();

      // search for new player range collisions
      for (auto &pIt1 : players_)
      {
        for (auto &pIt2 : players_)
        {
          // skip selfcompare
          if (pIt1.second.get() == pIt2.second.get()) continue;

          // check if player in range
          if (pIt1.second->isInRangeOf(*(pIt2.second)))
          {
            pIt1.second->registerPlayerMovementObserver(*(pIt2.second));
            pIt2.second->registerPlayerMovementObserver(*(pIt1.second));
          }
        }
      }

      // update current state
      websocket_server_.broadcastMessage(getJsonPlayerState());
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(Game::UPDATE_CYCLE_MS));
  }
}

/*--------------------------------------------------------------------------------------------------------------------*/
std::string Game::getJsonPlayerState() const
{
  std::stringstream ss;

  ss << "{\"players\":[";
  for(auto p = players_.begin(); p != players_.end();p++)
  {
    if(p != players_.begin())
      ss << ", ";

    ss << "{\"id\": " << p->second->getId()
    << ",\"x\": " << p->second->getPosition().x()
    << ",\"y\": " << p->second->getPosition().y()
    << ",\"observers\":[";

    for(auto o : p->second->getObservers())
    {
      if(o != *(p->second->getObservers().begin()))
        ss << ", ";
      ss << o->getPlayer().getId();
    }
    ss << "]}" << endl;
  }
  ss << "]}";
  return ss.str();
}
