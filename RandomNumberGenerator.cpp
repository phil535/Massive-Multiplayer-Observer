#include "RandomNumberGenerator.h"

RandomNumberGenerator &RandomNumberGenerator::instance()
{
  static RandomNumberGenerator random_number_generator_singleton;
  return random_number_generator_singleton;
}

RandomNumberGenerator::RandomNumberGenerator() : random_device_(), random_generator_(random_device_)
{
}

Position RandomNumberGenerator::getRandomPosition(const Position &max)
{
  if (max.getX() <= 1 || max.getY() <= 1) return Position(0, 0);

  std::uniform_int_distribution<> xDistribution(0, max.getX() - 1);
  std::uniform_int_distribution<> yDistribution(0, max.getY() - 1);

  return Position(xDistribution(random_generator_), yDistribution(random_generator_));
}