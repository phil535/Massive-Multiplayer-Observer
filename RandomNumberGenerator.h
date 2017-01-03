#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include <random>
#include "Position.h"

class RandomNumberGenerator
{
  public:
    RandomNumberGenerator &instance();

    Position getRandomPosition() const;

  private:
    RandomNumberGenerator();

    RandomNumberGenerator(const RandomNumberGenerator &rhs);

    RandomNumberGenerator &operator=(const RandomNumberGenerator &rhs);

  private:
    std::random_device random_device_;
    std::mt19937 random_generator_;

};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
