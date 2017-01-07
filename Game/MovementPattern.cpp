//
// Created by phil on 1/7/17.
//

#include "MovementPattern.h"
#include "Game.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern::MovementPattern()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
IdleMovementPattern::IdleMovementPattern()
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i IdleMovementPattern::move(Position &current_position)
{
  return {0,0};
}

/*--------------------------------------------------------------------------------------------------------------------*/
LinearMovementPattern::LinearMovementPattern(Direction direction) : direction_(direction)
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