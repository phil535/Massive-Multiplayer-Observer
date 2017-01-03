
#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <random>
#include "Position.h"

class Player
{
  public:

    Player();

    Player(const int & pos_x, const int & pos_y);

    Player(const int & pos_x, const int & pos_y, const int & dir_x, const int & dir_y);

    const Position & getPosition(void) {return position_;}
    const Position & getDirection(void) {return direction_;}

  private:

    Position position_;
    Position direction_;


};
#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
