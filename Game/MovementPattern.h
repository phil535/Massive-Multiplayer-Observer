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
      CIRCULAR,

      MAX
    };
  public:
    MovementPattern(std::string name);

    void setStartPosition(Position &start_position){ start_position_ = start_position;}

    const std::string &getName()const{return name_;};
    virtual Vec2i move(Position &current_position) = 0;

  protected:
    std::string name_;
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
    HarmonicMovementPattern(Direction direction, size_t amplitude, size_t period);
    virtual Vec2i move(Position &current_position);

  private:
    Direction direction_;
    double amplitude_;
    double period_;
    double phi_;
    double t_;
    long periods_;
};

class CircularMovementPattern : public MovementPattern
{
  public:
    CircularMovementPattern();
    virtual Vec2i move(Position &current_position);

  private:
    enum RotationDirection
    {
      CW,
      CCW
    };
    int phi_;
    int radius_;
    Position center_;
    RotationDirection rotation_;
    bool centered_;

};

#endif //GAME_MOVEMENTPATTERN_H
