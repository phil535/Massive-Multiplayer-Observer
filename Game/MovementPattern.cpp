//
// Created by phil on 1/7/17.
//

#include "MovementPattern.h"
#include "Game.h"
#include "Player.h"
#include <cmath>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>

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

  current_position %= Game::BOARD_SIZE;
  if(current_position.x() < 0) current_position.x() += Game::BOARD_SIZE.x();
  if(current_position.y() < 0) current_position.y() += Game::BOARD_SIZE.y();

  return current_position - old_position;
}

/*--------------------------------------------------------------------------------------------------------------------*/
HarmonicMovementPattern::HarmonicMovementPattern(Direction direction, size_t amplitude, size_t period)
    : MovementPattern("harmonic"), phi_(0.0), direction_(direction), amplitude_(amplitude), period_(period), t_(0.0), periods_(0)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i HarmonicMovementPattern::move(Position &current_position)
{

  const double frequency = 1.0 / period_;
  const double omega = 2 * M_PI * frequency;

  if (t_ == period_)
  {
    periods_++;
    t_ = 0;
  }

  double arg = omega * t_;

  typedef boost::geometry::model::d2::point_xy<double> point;
  point sine_point(t_ + start_position_.x() + periods_ * period_, amplitude_ * std::sin(omega * t_ + phi_) + start_position_.y());

  boost::geometry::strategy::transform::translate_transformer<double, 2, 2> translate(sine_point.x(), sine_point.y());
  boost::geometry::strategy::transform::rotate_transformer<boost::geometry::degree, double, 2, 2> rotate(
      direction_.degree());
  boost::geometry::strategy::transform::ublas_transformer<double, 2, 2> translateRotate(
      prod(rotate.matrix(), translate.matrix()));

  point new_position(start_position_.x(), start_position_.y());
  translateRotate.apply(point(0, 0), new_position);

  auto delta = Position(new_position.x(), new_position.y()) - current_position;
  current_position = Position(new_position.x(), new_position.y());

  current_position %= Game::BOARD_SIZE;
  if (current_position.x() < 0) current_position.x() += Game::BOARD_SIZE.x();
  if (current_position.y() < 0) current_position.y() += Game::BOARD_SIZE.y();

  t_ += 1;

  return delta;

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