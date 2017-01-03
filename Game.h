#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>
#include <map>
#include <chrono>
#include <memory>

#include "Position.h"
#include "Player.h"
#include "RandomNumberGenerator.h"

class Game
{
    const int UPDATE_CYCLE_MS = 100;
  public:
    static Game &instance();

    static int run(const std::vector<const char *> &args);

    const Position getBoardSize(void) {return board_size_;}

  private:

    Game(void);

    Game(const Game &rhs);

    Game &operator=(const Game &rhs);

    void setBoardSize(const Position set_val = Position(1024, 1024));

    static void update();

    void addPlayer(Position pos, Position direction);

    void removePlayer(size_t id);

    bool running_;
    Position board_size_;
    std::map<size_t, std::unique_ptr<Player>> players_;
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
