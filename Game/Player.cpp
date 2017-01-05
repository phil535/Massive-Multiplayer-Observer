#include "Player.h"
#include "RandomNumberGenerator.h"
#include "Game.h"

size_t Player::object_counter_;

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(void) : id_(object_counter_++)
{
  auto board_size = Game::instance().getBoardSize();
  position_ = RandomNumberGenerator::instance().getRandomVector(Vec2i(0, 0), board_size - Vec2i(1, 1));
  direction_ = RandomNumberGenerator::instance().getRandomVector(Vec2i(-2, -2), Vec2i(2, 2));
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Position position) : id_(object_counter_++), position_(position)
{
  direction_ = RandomNumberGenerator::instance().getRandomVector(Vec2i(-2, -2), Vec2i(2, 2));
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Position position, Vec2i direction)
    : id_(object_counter_++), position_(position), direction_(direction)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::move(void)
{
  Position board_size = Game::instance().getBoardSize();
  int result_x = position_.x();
  int result_y = position_.x();

  if((position_.x() + direction_.x()) >= board_size.x())
  {
    result_x = 0;
  }
  else if((position_.x() + direction_.x()) < 0 )
  {
    result_x = board_size.x() - 1;
  }
  else
  {
    result_x = position_.x() + direction_.x();
  }


  if((position_.y() + direction_.y()) >= board_size.y())
  {
    result_y = 0;
  }
  else if((position_.y() + direction_.y()) < 0 )
  {
    result_y = board_size.y() - 1;
  }
  else
  {
    result_y = position_.y() + direction_.y();
  }

  position_ = Position(result_x, result_y);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerRegisterNotification(PlayerMovementSubject &player)
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerUnregisterNotification(PlayerMovementSubject &player)
{

}
/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerMovementNotification(PlayerMovementSubject &player, Distance &delta)
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "[" << rhs.getId() << "] pos" << rhs.getPosition() << ", dir" << rhs.getDirection();
  return stream;
}
