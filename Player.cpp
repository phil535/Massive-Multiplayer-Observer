#include "Player.h"
#include "RandomNumberGenerator.h"
#include "Game.h"

size_t Player::object_counter_;

std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "[" << rhs.getId() << "] pos" << rhs.getPosition() << ", dir" << rhs.getDirection();
  return stream;
}

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

Player & Player::operator++(void)
{
  Position board_size = Game::instance().getBoardSize();

}

/*--------------------------------------------------------------------------------------------------------------------*/

Player & Player::operator--(void)
{

}