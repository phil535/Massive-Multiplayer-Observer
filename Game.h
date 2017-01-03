#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>
#include "Position.h"
class Game
{
  public:
    static Game &instance();

    static int run(const std::vector<const char *> &args);

    const Position & getBoardSize(void) {return board_size_;}

  private:

    Game(void);

    Game(const Game &rhs);

    Game &operator=(const Game &rhs);

    Position board_size_;

    void setBoardSize( const Position & set_val = Position(1024, 1024));
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
