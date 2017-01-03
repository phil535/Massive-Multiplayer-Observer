#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>

class Game
{

  public:
    static Game &instance();

    static int run(const std::vector<const char *> &args);

  private:
    Game();

    Game(const Game &rhs);

    Game &operator=(const Game &rhs);

};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
