//
// Created by phil on 1/7/17.
//

#ifndef GAME_MOVEMENTPATTERN_H
#define GAME_MOVEMENTPATTERN_H

#include "Types.h"

class Player;

class MovementPattern
{
  public:
    MovementPattern(Position start_position);

    virtual void move(Player &player) = 0;

  private:
    Position start_position_;
};

class LinearMovementPattern : public MovementPattern
{
  public:
    LinearMovementPattern(Position start_position, Direction direction);
    virtual void move(Player &player);

  private:
    Direction direction_;
};

#endif //GAME_MOVEMENTPATTERN_H
