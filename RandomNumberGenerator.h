#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H


#include "Position.h"

class RandomNumberGenerator
{
  public:
    static RandomNumberGenerator &instance();

    Position getRandomPosition(const Position &max) const;

  private:
    RandomNumberGenerator();

    RandomNumberGenerator(const RandomNumberGenerator &rhs);

    RandomNumberGenerator &operator=(const RandomNumberGenerator &rhs);
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
