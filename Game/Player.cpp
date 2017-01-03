#include "Player.h"
#include "RandomNumberGenerator.h"
#include "Game.h"

size_t Player::object_counter_;

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(void) : id_(object_counter_++)
{
  Position board_size = Game::instance().getBoardSize();
  position_ = RandomNumberGenerator::instance().getRandomPosition(board_size);
  direction_ = RandomNumberGenerator::instance().getRandomDirection();
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(const int & pos_x, const int & pos_y)
    : id_(object_counter_++), position_(pos_x, pos_y)
{
  direction_ = RandomNumberGenerator::instance().getRandomDirection();
}

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(const int & pos_x, const int & pos_y, const int & dir_x, const int & dir_y)
    : id_(object_counter_++), position_(pos_x, pos_y),
      direction_(dir_x, dir_y)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::move(void)
{
  Position board_size = Game::instance().getBoardSize();
  int result_x = position_.getX();
  int result_y = position_.getY();

  if((position_.getX() + direction_.getX()) >= board_size.getX())
  {
    result_x = 0;
  }
  else if((position_.getX() + direction_.getX()) < 0 )
  {
    result_x = board_size.getX() - 1;
  }
  else
  {
    result_x = position_.getX() + direction_.getX();
  }


  if((position_.getY() + direction_.getY()) >= board_size.getY())
  {
    result_y = 0;
  }
  else if((position_.getY() + direction_.getY()) < 0 )
  {
    result_y = board_size.getY() - 1;
  }
  else
  {
    result_y = position_.getY() + direction_.getY();
  }

  position_ = Position(result_x, result_y);
}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "[" << rhs.getId() << "] pos" << rhs.getPosition() << ", dir" << rhs.getDirection();
  return stream;
}