#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <thread>

#include "Game.h"
#include "MovementPattern.h"


using std::cout;
using std::endl;

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

    std::vector<std::string> parameters;
    std::istringstream iss(input_buffer);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(parameters));

    std::string &command = parameters.at(0);

    if (command == "quit")
    {
      running_ = false;
      break;
    }
    else if (command == "add")
    {
      if(parameters.size() == 1)
      {
        addPlayer();
        continue;
      }
      else if(parameters.size() == 2)
      {
        int player_count = 0;
        try
        {
          player_count = std::stoul(parameters.at(1));
          for (; player_count--;)
          {
            {
              std::lock_guard<std::mutex> lock(mutex_players_);

              auto &new_player = addPlayer();
              new_player.setStrategy(std::unique_ptr<MovementPattern>(RandomNumberGenerator::instance().getRandomMovementPattern()));
            }
          }
        }
        catch(...)
        {
          cout << "usage: add [#] [linear,harmonic,circular]" << endl;
        }
      }
      else
      {
        int player_count = 0;
        try{player_count = std::stoul(parameters.at(1));}catch(...){continue;}

        if(parameters.size() >= 3)
        {
          if(parameters.at(2) == "linear")
          {
            for (; player_count--;)
            {
              {
                std::lock_guard<std::mutex> lock(mutex_players_);
                auto &new_player = addPlayer();
                new_player.setStrategy(std::unique_ptr<MovementPattern>(
                    new LinearMovementPattern(RandomNumberGenerator::instance().getRandomDirection())));
              }
            }

          }
          else if(parameters.at(2) == "harmonic")
          {
            for (; player_count--;)
            {
              {
                std::lock_guard<std::mutex> lock(mutex_players_);
                auto &new_player = addPlayer();
                new_player.setStrategy(std::unique_ptr<MovementPattern>(new HarmonicMovementPattern(RandomNumberGenerator::instance().getRandomDirection())));
              }
            }
          }
          else if(parameters.at(2) == "circular")
          {
            for (; player_count--;)
            {
              {
                std::lock_guard<std::mutex> lock(mutex_players_);
                auto &new_player = addPlayer();
                new_player.setStrategy(std::unique_ptr<MovementPattern>(new CircularMovementPattern()));
              }
            }
          }
          else
          {
            cout << "usage: add [#] [linear,harmonic,circular]" << endl;
          }
        }
      }
    }
    else if (command == "list")
    {
      if(players_.size() == 0)
        cout << "No players in game." << endl;

      for (auto &p : players_)
        cout << *(p.second) << endl;
    }
    else if(command == "test")
    {
      unsigned long test_number = 1;
      try
      {
        test_number = std::stoul(parameters.at(1));
        switch(test_number)
        {
          case 1:
            {
              addPlayer({400,400});
              addPlayer({200,400});
            }
            break;
          case 2:
            {
              addPlayer({0,0});
              addPlayer({799,0});
              addPlayer({799,799});
              addPlayer({0,799});
            }
            break;
          default:
            cout << "Unknown test" << endl;
            break;
        }
      }
      catch(...)
      {
        cout << "usage: test [1-2]" << endl;
      }
    }
    else if(command == "debug")
    {
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
    else
    {
      cout << "Unknown command." << endl;
    }
  }

  players_.clear();

  // stop gameloop
  update_thread.join();

  // stop websocketserver
  websocket_server_.stop();
  websocket_thread.join();

  return 0;
}


/*--------------------------------------------------------------------------------------------------------------------*/
Player &Game::addPlayer(Position position)
{
  std::unique_ptr<Player> new_player(new Player(*this, position));
  size_t id = new_player->getId();
  cout << "Added new: " << *new_player << endl;
  players_.insert(std::make_pair(new_player->getId(), std::move(new_player)));

  return *(players_[id].get());
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player &Game::addPlayer(void)
{
  return addPlayer(RandomNumberGenerator::instance().getRandomVector({0,0}, BOARD_SIZE - 1));
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::removePlayer(size_t id)
{
  players_.erase(id);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Game::update()
{
  for (;running_;)
  {
    {
      std::lock_guard<std::mutex> lock(mutex_players_);

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
