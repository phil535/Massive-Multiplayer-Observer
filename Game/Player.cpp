#include "Player.h"
#include "Game.h"

size_t Player::object_counter_;

/*--------------------------------------------------------------------------------------------------------------------*/
Player::Player(Position position, MovementPattern *strategy) : PlayerMovementSubject(*this),
                                                                           PlayerMovementObserver(*this),
                                                                           id_(object_counter_++), position_(position),
                                                                           movement_strategy_(strategy)
{
  if(movement_strategy_)
    movement_strategy_->setStartPosition(position_);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bool Player::isInRangeOf(Player &player) const
{
  static const size_t squared_range = RANGE * RANGE;
  return (position_.euclideanDistanceSquared(player.position_) <= squared_range) ? true : false;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::setStrategy(MovementPattern *strategy)
{
  movement_strategy_.reset(strategy);

  if(movement_strategy_)
    movement_strategy_->setStartPosition(position_);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::move(void)
{
  auto delta = movement_strategy_->move(position_);

  // notify all observers about player movement
  if(delta != 0) notifyPlayerMovementObservers(delta);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerRegisterNotification(Player &player)
{
  //std::cout << "Register notification:   " << player << " -> " << *this << std::endl << std::flush;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerUnregisterNotification(Player &player)
{
  //std::cout << "Unregister notification: " << player << " -> " << *this << std::endl << std::flush;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void Player::playerMovementNotification(Player &player, Distance &delta)
{
  //std::cout << "Movement notification:   " << player << " -> " << *this << std::endl << std::flush;
}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Player &rhs)
{
  stream << "Player[" << rhs.getId() << "] " << rhs.position_;
  if(rhs.movement_strategy_) stream << " " << rhs.movement_strategy_->getName();
  return stream;
}
