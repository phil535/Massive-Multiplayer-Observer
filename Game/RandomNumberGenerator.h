#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include "Types.h"
#include "MovementPattern.h"

class RandomNumberGenerator
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
    const MovementPattern::Strategy RANDOM_MOVEMENT_STRATEGIES[(int)MovementPattern::Strategy::MAX] = {};
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
    MovementPattern *getRandomMovementPattern(Position &start_position)const;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
