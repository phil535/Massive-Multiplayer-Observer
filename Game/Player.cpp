#include "Player.h"
#include "RandomNumberGenerator.h"
#include "Game.h"

size_t Player::object_counter_;

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(void) : PlayerMovementSubject(*this), PlayerMovementObserver(*this), id_(object_counter_++),
                       position_(0), direction_(0)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Position position, Vec2i direction) : PlayerMovementSubject(*this), PlayerMovementObserver(*this),
                                                     id_(object_counter_++), position_(position), direction_(direction)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
bool Player::isInRangeOf(Player &player) const
{
  return (position_.euclideanDistance(player.position_) <= RANGE) ? true : false;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::move(Vec2i delta)
{
  Position board_size = Game::instance().getBoardSize();
  int result_x = position_.x();
  int result_y = position_.x();

  if((position_.x() + delta.x()) >= board_size.x())
  {
    result_x = 0;
  }
  else if((position_.x() + delta.x()) < 0 )
  {
    result_x = board_size.x() - 1;
  }
  else
  {
    result_x = position_.x() + delta.x();
  }

  if((position_.y() + delta.y()) >= board_size.y())
  {
    result_y = 0;
  }
  else if((position_.y() + delta.y()) < 0 )
  {
    result_y = board_size.y() - 1;
  }
  else
  {
    result_y = position_.y() + delta.y();
  }

  position_ = Position(result_x, result_y);

  // notify all observers about player movement
  notifyPlayerMovementObservers(delta);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerRegisterNotification(Player &player)
{
  std::cout << player << " registered @" << *this << std::endl;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerUnregisterNotification(Player &player)
{
  std::cout << player << " unregistered @" << *this << std::endl;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerMovementNotification(Player &player, Distance &delta)
{
  std::cout << player << " moved by " << delta << " in sight of " << *this << std::endl;
}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "[" << rhs.getId() << "] pos" << rhs.getPosition() << ", dir" << rhs.getDirection();
  return stream;
}
