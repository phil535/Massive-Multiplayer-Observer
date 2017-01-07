#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>
#include <map>
#include <chrono>
#include <memory>

#include "WebsocketServer.h"
#include "Types.h"
#include "Player.h"
#include "RandomNumberGenerator.h"

class Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constants
    const int UPDATE_CYCLE_MS = 20;
  public:
    static const Size BOARD_SIZE;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    Game(void);
    ~Game(void);
  private:
    Game(const Game &rhs);
    Game &operator=(const Game &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
  public:
    int run(const std::vector<std::string> &args);
  private:
    void update();

    void addPlayer(void);
    void addPlayer(Position pos);


    void removePlayer(size_t id);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
  public:
    std::string getJsonPlayerState(void) const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    bool running_;
    std::map<size_t, std::unique_ptr<Player>> players_;
    WebsocketServer websocket_server_;
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
