#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>
#include <map>
#include <chrono>
#include <memory>

#include "WebsocketServer.h"
#include "Position.h"
#include "Player.h"
#include "RandomNumberGenerator.h"

class Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constants
    const int UPDATE_CYCLE_MS = 100;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  private:
    Game(void);

  public:
    static Game &instance();

  private:
    Game(const Game &rhs);
    Game &operator=(const Game &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    static int run(const std::vector<const char *> &args);
    static void update();

    void addPlayer(Position pos, Position direction);
    void addPlayer(void);
    void removePlayer(size_t id);

    void save(void);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    const Position getBoardSize(void) {return board_size_;}
    void setBoardSize(const Position set_val = Position(1024, 1024));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    bool running_;
    Position board_size_;
    std::map<size_t, std::unique_ptr<Player>> players_;
    WebsocketServer websocket_server_;
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
