//
// Created by phil on 1/7/17.
//

#include "MovementPattern.h"
#include "Game.h"
#include "Player.h"
#include <cmath>

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern::MovementPattern(std::string name) : name_(name)
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
IdleMovementPattern::IdleMovementPattern() : MovementPattern("idle")
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i IdleMovementPattern::move(Position &current_position)
{
  return {0,0};
}

/*--------------------------------------------------------------------------------------------------------------------*/
LinearMovementPattern::LinearMovementPattern(Direction direction) : MovementPattern("linear"), direction_(direction)
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i LinearMovementPattern::move(Position &current_position)
{
  if(direction_ == 0) return {0,0};

  Position old_position = current_position;

  current_position += direction_;

  if(current_position.x() < 0)
    current_position.x() = Game::BOARD_SIZE.x() - 1;
  if(current_position.x() > Game::BOARD_SIZE.x())
    current_position.x() = 0;
  if(current_position.y() < 0)
    current_position.y() = Game::BOARD_SIZE.y() - 1;
  if(current_position.y() > Game::BOARD_SIZE.y())
    current_position.y() = 0;

  return current_position - old_position;
}

/*--------------------------------------------------------------------------------------------------------------------*/
HarmonicMovementPattern::HarmonicMovementPattern(Direction direction)
    : MovementPattern("harmonic"), phi_(0), direction_(direction)
{
  speed_tick_ = RandomNumberGenerator::instance().getRandomInt(1,2);
  relative_position_ = Position(0, 0);
  amplitude_ = RandomNumberGenerator::instance().getRandomInt(1, 8);

  if(direction_.x() && direction_.y())
    direction_.y() = 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i HarmonicMovementPattern::move(Position & current_position)
{
  if(phi_ == 360)
  {
    relative_position_ = Position(0, 0);
    phi_ = 0;
  }
  Position old_pos = current_position;
  Position new_pos;
  double x_result, y_result;
  y_result = (double)amplitude_ * sin((double)phi_*(double)M_PI/(double)180);
  x_result = relative_position_.x() + speed_tick_;


  if(direction_.x() == 1)
  {
    new_pos = Position((int)x_result, (int)y_result) + current_position;
  }
  else if(direction_.x() == -1)
  {
    new_pos = Position(0 - (int)x_result, 0 - (int)y_result) + current_position;
  }
  else if(direction_.y() == 1)
  {
    new_pos = Position(0 - (int)y_result, (int)x_result) + current_position;
  }
  else if(direction_.y() == -1)
  {
    new_pos = Position((int)y_result, 0 - (int)x_result) + current_position;
  }

  if(new_pos.x() < 0)
    new_pos.x() = Game::BOARD_SIZE.x() - 1;
  if(new_pos.x() > Game::BOARD_SIZE.x())
    new_pos.x() = 0;
  if(new_pos.y() < 0)
    new_pos.y() = Game::BOARD_SIZE.y() - 1;
  if(new_pos.y() > Game::BOARD_SIZE.y())
    new_pos.y() = 0;

  current_position = new_pos;
  phi_ += 1;

  return current_position - old_pos;
}

/*--------------------------------------------------------------------------------------------------------------------*/
CircularMovementPattern::CircularMovementPattern()
    : MovementPattern("circular"), phi_(0)
{
  radius_ = RandomNumberGenerator::instance().getRandomInt(50, 300);

  if(RandomNumberGenerator::instance().getRandomInt(0, 1))
    rotation_ = RotationDirection::CW;
  else
    rotation_ = RotationDirection::CCW;
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i CircularMovementPattern::move(Position & current_position)
{

  if (!centered_)
  {
    int tmp_center = start_position_.x() - radius_;
    if (tmp_center < 0)
      tmp_center += 2 * radius_;
    center_ = Position(tmp_center, start_position_.y());
    centered_ = true;
  }

  if(phi_ == 360)
  {
    phi_ = 0;
  }
  Position old_pos = current_position;

  double x_result, y_result;
  y_result = radius_ * sin((double)phi_*(double)M_PI/(double)180);
  x_result = radius_ * cos((double)phi_*(double)M_PI/(double)180);

  Position new_pos((int)x_result, (int)y_result);
  new_pos = center_ + new_pos;

  if(new_pos.x() < 0)
    new_pos.x() = Game::BOARD_SIZE.x() + new_pos.x();
  if(new_pos.x() > Game::BOARD_SIZE.x())
    new_pos.x() = new_pos.x() - Game::BOARD_SIZE.x();
  if(new_pos.y() < 0)
    new_pos.y() = Game::BOARD_SIZE.y() + new_pos.y();
  if(new_pos.y() > Game::BOARD_SIZE.y())
    new_pos.y() = new_pos.y() - Game::BOARD_SIZE.y();

  current_position = new_pos;
  phi_ += 1;
  return current_position - old_pos;
}