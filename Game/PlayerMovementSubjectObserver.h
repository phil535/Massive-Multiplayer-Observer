#ifndef GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
#define GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H

#include "Types.h"
#include <unordered_set>

class PlayerMovementSubject;

class PlayerMovementObserver
{
  public:
    virtual void playerMovementNotification(PlayerMovementSubject &player, Distance &delta) = 0;
};

class PlayerMovementSubject
{
    std::unordered_set<PlayerMovementObserver*> observers_;
  public:
    void registerPlayerMovementObserver(PlayerMovementObserver &observer);
    void unregisterPlayerMovementObserver(PlayerMovementObserver &observer);
    void notifyPlayerMovementObservers(Distance &delta);

    virtual void playerRegisterNotification(PlayerMovementSubject &player) = 0;
    virtual void playerUnregisterNotification(PlayerMovementSubject &player) = 0;
};


#endif //GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
