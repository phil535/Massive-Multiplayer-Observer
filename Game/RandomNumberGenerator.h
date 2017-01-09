#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include "Types.h"
#include "MovementPattern.h"

class RandomNumberGenerator
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    static RandomNumberGenerator &instance(void);
  private:
    RandomNumberGenerator(void);
    RandomNumberGenerator(const RandomNumberGenerator &rhs);
    RandomNumberGenerator &operator=(const RandomNumberGenerator &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
  public:
    int getRandomInt(int min, int max) const;
    Vec2i getRandomVector(Vec2i min, Vec2i max) const;
    Vec2i getRandomDirection(void) const;
    MovementPattern *getRandomMovementPattern(void) const;
    MovementPattern *getRandomMovementPattern(MovementPattern::Strategy strategy) const;

};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
