#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>
#include <map>
#include <chrono>
#include "Position.h"
#include "Player.h"

class Game
{
    const int UPDATE_CYCLE_MS = 100;
  public:
    static Game &instance();

    static int run(const std::vector<const char *> &args);

    const Position & getBoardSize(void) {return board_size_;}

  private:

    Game(void);

    Game(const Game &rhs);

    Game &operator=(const Game &rhs);

    void setBoardSize( const Position & set_val = Position(1024, 1024));

    static void update();

    bool running_;
    Position board_size_;
    std::map<size_t, Player> players_;
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
