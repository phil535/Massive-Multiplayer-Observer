#ifndef GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
#define GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H

#include "Types.h"
#include <unordered_set>

class Player;

class PlayerMovementObserver
{
    friend class PlayerMovementSubject;
    Player &player_;
  public:
    PlayerMovementObserver(Player &player);
    enum REGISTER_RESULT
    {
      NEW_PLAYER,
      ALREADY_EXISTS
    };
    virtual void playerMovementNotification(Player &player, Distance &delta) = 0;
};

class PlayerMovementSubject
{
    friend class PlayerMovementObserver;
    Player &player_;
    std::unordered_set<PlayerMovementObserver*> observers_;
  public:
    PlayerMovementSubject(Player &player);
    PlayerMovementObserver::REGISTER_RESULT registerPlayerMovementObserver(PlayerMovementObserver &observer);
    void unregisterPlayerMovementObserver(PlayerMovementObserver &observer);
    void notifyPlayerMovementObservers(Distance &delta);

    virtual void playerRegisterNotification(Player &player) = 0;
    virtual void playerUnregisterNotification(Player &player) = 0;
};


#endif //GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
