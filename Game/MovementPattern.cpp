//
// Created by phil on 1/7/17.
//

#include "MovementPattern.h"
#include "Game.h"
#include "Player.h"
#include <cmath>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>

typedef boost::geometry::model::d2::point_xy<double> BoostPoint2d;
using boost::geometry::strategy::transform::translate_transformer;
using boost::geometry::strategy::transform::rotate_transformer;
using boost::geometry::strategy::transform::ublas_transformer;

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern::MovementPattern(std::string name) : name_(name)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
IdleMovementPattern::IdleMovementPattern(void) : MovementPattern("idle")
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

  current_position %= Game::BOARD_SIZE;
  if(current_position.x() < 0) current_position.x() += Game::BOARD_SIZE.x();
  if(current_position.y() < 0) current_position.y() += Game::BOARD_SIZE.y();

  return current_position - old_position;
}

/*--------------------------------------------------------------------------------------------------------------------*/
HarmonicMovementPattern::HarmonicMovementPattern(Direction direction, size_t amplitude, size_t period)
    : MovementPattern("harmonic"), direction_(direction), amplitude_(amplitude), period_(period), phi_(0.0), t_(0.0)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i HarmonicMovementPattern::move(Position &current_position)
{
  t_ += direction_.length();

  if (t_ >= Game::BOARD_SIZE.x() * Game::BOARD_SIZE.y())
    t_ -= period_;

  const double frequency = 1.0 / period_;
  const double omega = 2 * M_PI * frequency;
  BoostPoint2d sine_point(t_, -amplitude_ * std::sin(omega * t_ + phi_)); // negative value to invert y-axis

  translate_transformer<double, 2, 2> sine_translation(sine_point.x(), sine_point.y());
  rotate_transformer<boost::geometry::radian, double, 2, 2> rotate(direction_.radian());

  ublas_transformer<double, 2, 2> translateRotate(prod(rotate.matrix(), sine_translation.matrix()));
  BoostPoint2d translate_rotate_position;
  translateRotate.apply(BoostPoint2d(0.0, 0.0), translate_rotate_position);

  Vec2i new_position(static_cast<int>(translate_rotate_position.x() + start_position_.x()),
                     static_cast<int>(translate_rotate_position.y() + start_position_.y()));

  Vec2i delta = current_position - new_position;
  current_position = new_position;

  current_position %= Game::BOARD_SIZE;
  if (current_position.x() < 0) current_position.x() += Game::BOARD_SIZE.x();
  if (current_position.y() < 0) current_position.y() += Game::BOARD_SIZE.y();

  return delta;
}

/*--------------------------------------------------------------------------------------------------------------------*/
CircularMovementPattern::CircularMovementPattern(void)
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
  y_result = radius_ * sin((double)phi_*(double)M_PI / (double)180);
  x_result = radius_ * cos((double)phi_*(double)M_PI / (double)180);

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