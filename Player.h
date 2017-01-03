
#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <random>
#include "Position.h"

class Player
{
  public:

    Player(const int & pos_x, const int & pos_y) : position_(pos_x, pos_y) {}

    Player() {}

  private:

    Position position_;


};
#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
