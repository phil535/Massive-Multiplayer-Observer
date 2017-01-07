#include "RandomNumberGenerator.h"
#include "Game.h"

#include <array>
#include <cstdlib>
#include <ctime>

/*--------------------------------------------------------------------------------------------------------------------*/
RandomNumberGenerator &RandomNumberGenerator::instance()
{
  static RandomNumberGenerator random_number_generator_singleton;
  return random_number_generator_singleton;
}

/*--------------------------------------------------------------------------------------------------------------------*/
RandomNumberGenerator::RandomNumberGenerator()
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
Vec2i RandomNumberGenerator::getRandomDirection()const
{
  std::array<Vec2i, 8> RANDOM_DIRECTIONS = {
      {
          Direction(0, 1),
          Direction(1, 1),
          Direction(1, 0),
          Direction(1,-1),
          Direction(0, -1),
          Direction(-1, -1),
          Direction(-1,0),
          Direction(-1,1)
      }};

  return RANDOM_DIRECTIONS.at(getRandomInt(0, 7));
}

/*--------------------------------------------------------------------------------------------------------------------*/
MovementPattern *RandomNumberGenerator::getRandomMovementPattern()const
{
  switch(getRandomInt(0, (int)MovementPattern::Strategy::MAX - 1))
  {
    case (int)MovementPattern::Strategy::IDLE:
      return new IdleMovementPattern();
    case (int)MovementPattern::Strategy::LINEAR:
      return new LinearMovementPattern(RandomNumberGenerator::instance().getRandomDirection());
  }
  return nullptr;
}
