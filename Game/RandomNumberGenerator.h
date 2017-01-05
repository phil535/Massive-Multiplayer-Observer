#ifndef MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
#define MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H

#include "Types.h"

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
  private:
    int getRandomInt(int min, int max) const;
  public:
    Vec2i getRandomVector(Vec2i min, Vec2i max) const;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_RANDOMNUMBERGENERATOR_H
