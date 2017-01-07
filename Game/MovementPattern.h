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
    enum class Strategy
    {
      IDLE,
      LINEAR,

      MAX
    };
  public:
    MovementPattern(Position start_position);
    virtual Vec2i move(Position &current_position) = 0;

  private:
    Position start_position_;
};

class IdleMovementPattern : public MovementPattern
{
  public:
    IdleMovementPattern();
    virtual Vec2i move(Position &current_position);
};

class LinearMovementPattern : public MovementPattern
{
  public:
    LinearMovementPattern(Position start_position, Direction direction);
    virtual Vec2i move(Position &current_position);

  private:
    Direction direction_;
};

#endif //GAME_MOVEMENTPATTERN_H
