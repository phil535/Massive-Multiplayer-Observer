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
      HARMONIC,

      MAX
    };
  public:
    MovementPattern();

    void setStartPosition(Position &start_position){ start_position_ = start_position;}

    virtual Vec2i move(Position &current_position) = 0;

  protected:
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
    LinearMovementPattern(Direction direction);
    virtual Vec2i move(Position &current_position);

  private:
    Direction direction_;
};

class HarmonicMovementPattern : public MovementPattern
{
  public:
    HarmonicMovementPattern(Position start_position, Direction direction);
    virtual Vec2i move(Position &current_position);

  private:
    Direction direction_;
    Position relative_position_;
    int phi_;
    int speed_tick_;
    int amplitude_;
};

#endif //GAME_MOVEMENTPATTERN_H
