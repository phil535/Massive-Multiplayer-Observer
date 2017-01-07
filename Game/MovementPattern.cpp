//
// Created by phil on 1/7/17.
//

#include "MovementPattern.h"
#include "Game.h"
#include "Player.h"

MovementPattern::MovementPattern(Position start_position) : start_position_(start_position)
{

}

LinearMovementPattern::LinearMovementPattern(Position start_position, Direction direction) : MovementPattern(start_position), direction_(direction)
{

}
void LinearMovementPattern::move(Player &player)
{
  if(direction_ == 0) return;

  Position &current_position = player.getPosition();
  Game &game = player.getGame();

  current_position += direction_;

  if(current_position.x() < 0)
    current_position.x() = game.BOARD_SIZE.x() - 1;
  if(current_position.x() > game.BOARD_SIZE.x())
    current_position.x() = 0;
  if(current_position.y() < 0)
    current_position.y() = game.BOARD_SIZE.y() - 1;
  if(current_position.y() > game.BOARD_SIZE.y())
    current_position.y() = 0;

  // notify all observers about player movement
  player.notifyPlayerMovementObservers(direction_);
}