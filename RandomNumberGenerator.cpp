#include "RandomNumberGenerator.h"

#include <cstdlib>
#include <ctime>

RandomNumberGenerator &RandomNumberGenerator::instance()
{
  static RandomNumberGenerator random_number_generator_singleton;
  return random_number_generator_singleton;
}

RandomNumberGenerator::RandomNumberGenerator()
{
  std::srand(std::time(0));
}

Position RandomNumberGenerator::getRandomPosition(const Position &max) const
{

  if (max.getX() == 0 || max.getY() == 0) return Position(0, 0);

  return Position(std::rand() % (max.getX() - 1), std::rand() % (max.getY() - 1));
}