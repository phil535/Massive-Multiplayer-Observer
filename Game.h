//
// Created by phil on 1/3/17.
//

#ifndef MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
#define MASSIVE_MULTIPLAYER_OBSERVER_GAME_H

#include <vector>

class Game
{
    const std::vector<const char *> &args_;
  public:
    Game(const std::vector<const char *> &args);

    int run();
};


#endif //MASSIVE_MULTIPLAYER_OBSERVER_GAME_H
