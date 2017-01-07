#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include "Types.h"
#include "MovementPattern.h"

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
    int getRandomInt(int min, int max) const;
    Vec2i getRandomVector(Vec2i min, Vec2i max) const;
    Vec2i getRandomDirection()const;
    MovementPattern *getRandomMovementPattern()const;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
