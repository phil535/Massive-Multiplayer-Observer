#include "RandomNumberGenerator.h"
#include "Game.h"

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
MovementPattern *RandomNumberGenerator::getRandomMovementPattern(Position &start_position)const
{
  //switch(getRandomInt(0, (int)MovementPattern::Strategy::MAX - 1))
  switch((int)MovementPattern::Strategy::LINEAR)
  {
    case (int)MovementPattern::Strategy::IDLE:
      return new IdleMovementPattern();
    case (int)MovementPattern::Strategy::LINEAR:
      return new LinearMovementPattern(start_position, RandomNumberGenerator::instance().getRandomVector({-1,-1}, {1,1}));
  }
  return nullptr;
}
