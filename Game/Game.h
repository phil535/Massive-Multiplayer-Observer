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
    const int UPDATE_CYCLE_MS = 100;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    static Game &instance();

  private:
    Game(void);
    Game(const Game &rhs);
    Game &operator=(const Game &rhs);
    ~Game(void);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
  public:
    static int run(const std::vector<const char *> &args);
  private:
    static void update();

    void addPlayer(Position pos, Position direction);
    void addPlayer(void);
    void removePlayer(size_t id);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
  public:
    std::string getJsonPlayerState(void) const;

    const Vec2i &getBoardSize(void) {return board_size_;}
  private:
    void setBoardSize(Vec2i size = Vec2i(1024, 1024));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    bool running_;
    Vec2i board_size_;
    std::map<size_t, std::unique_ptr<Player>> players_;
    WebsocketServer websocket_server_;
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
