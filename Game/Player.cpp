#include "Player.h"
#include "Game.h"

size_t Player::object_counter_;

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Game &game) : game_(game), PlayerMovementSubject(*this), PlayerMovementObserver(*this), id_(object_counter_++),
                       position_(0), direction_(0)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Game &game, Position position, Vec2i direction) : game_(game), PlayerMovementSubject(*this), PlayerMovementObserver(*this),
                                                     id_(object_counter_++), position_(position), direction_(direction)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
bool Player::isInRangeOf(Player &player) const
{
  static const size_t squared_range = RANGE * RANGE;
  return (position_.euclideanDistanceSquared(player.position_) <= squared_range) ? true : false;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::move(Vec2i delta)
{
  position_ += delta;

  if(position_.x() < 0)
    position_.x() = game_.BOARD_SIZE.x() - 1;
  if(position_.x() > game_.BOARD_SIZE.x())
    position_.x() = 0;
  if(position_.y() < 0)
    position_.y() = game_.BOARD_SIZE.y() - 1;
  if(position_.y() > game_.BOARD_SIZE.y())
    position_.y() = 0;

  // notify all observers about player movement
  if(delta != 0) notifyPlayerMovementObservers(delta);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerRegisterNotification(Player &player)
{
  std::cout << "Register notification:   " << player << " -> " << *this << std::endl << std::flush;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerUnregisterNotification(Player &player)
{
  std::cout << "Unregister notification: " << player << " -> " << *this << std::endl << std::flush;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerMovementNotification(Player &player, Distance &delta)
{
  //std::cout << "Movement notification:   " << player << " -> " << *this << std::endl << std::flush;
}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "Player[" << rhs.getId() << "]";
  return stream;
}
