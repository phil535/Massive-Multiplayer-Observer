#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include "Position.h"

class RandomNumberGenerator
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    static RandomNumberGenerator &instance();
  private:
    RandomNumberGenerator();
    RandomNumberGenerator(const RandomNumberGenerator &rhs);
    RandomNumberGenerator &operator=(const RandomNumberGenerator &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
  public:
    Position getRandomPosition(const Position &max) const;
    Position getRandomDirection() const;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
