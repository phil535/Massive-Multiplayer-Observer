#include "RandomNumberGenerator.h"
#include "Game.h"

#include <array>
#include <cstdlib>
#include <ctime>

/*--------------------------------------------------------------------------------------------------------------------*/
RandomNumberGenerator &RandomNumberGenerator::instance(void)
{
  static RandomNumberGenerator random_number_generator_singleton;
  return random_number_generator_singleton;
}

/*--------------------------------------------------------------------------------------------------------------------*/
RandomNumberGenerator::RandomNumberGenerator(void)
{
  std::srand(std::time(0));
}
int RandomNumberGenerator::getRandomInt(int min, int max) const
{
  return min + rand() % (max + 1 - min);
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i RandomNumberGenerator::getRandomVector(Vec2i min_vec, Vec2i max_vec) const
{
  return Vec2i(getRandomInt(min_vec.x(), max_vec.x()), getRandomInt(min_vec.y(), max_vec.y()));
}

/*--------------------------------------------------------------------------------------------------------------------*/
Vec2i RandomNumberGenerator::getRandomDirection(void)const
{
  std::array<Vec2i, 8> RANDOM_DIRECTIONS = {
      {
          Direction(0, 1),
          Direction(1, 1),
          Direction(1, 0),
          Direction(1, -1),
          Direction(0, -1),
          Direction(-1, -1),
          Direction(-1, 0),
          Direction(-1, 1)
      }};

  return RANDOM_DIRECTIONS.at(getRandomInt(0, 7));
}

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern *RandomNumberGenerator::getRandomMovementPattern(void)const
{
  return instance().getRandomMovementPattern((MovementPattern::Strategy)getRandomInt(0, (int)MovementPattern::Strategy::MAX - 1));
}

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern *RandomNumberGenerator::getRandomMovementPattern(MovementPattern::Strategy strategy)const
{
  switch(strategy)
  {
    case MovementPattern::Strategy::IDLE:
      return new IdleMovementPattern();
    case MovementPattern::Strategy::LINEAR:
      return new LinearMovementPattern(RandomNumberGenerator::instance().getRandomDirection());
    case MovementPattern::Strategy::HARMONIC:
    {
      return new HarmonicMovementPattern(RandomNumberGenerator::instance().getRandomDirection(),
                                         RandomNumberGenerator::instance().getRandomInt(100, Game::BOARD_SIZE.x() / 3),
                                         RandomNumberGenerator::instance().getRandomInt(50, Game::BOARD_SIZE.x() * 2));
    }
    case MovementPattern::Strategy::CIRCULAR:
      return new CircularMovementPattern();
    default:
      return nullptr;
  }
}

