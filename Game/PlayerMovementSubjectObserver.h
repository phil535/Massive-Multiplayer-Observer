#ifndef GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
#define GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H

#include <glm/glm.hpp>
#include <unordered_set>

class PlayerMovementSubject;

class PlayerMovementObserver
{
  public:
    virtual void playerMovementNotification(PlayerMovementSubject &player, glm::ivec2 &delta) = 0;
};

class PlayerMovementSubject
{
    std::unordered_set<PlayerMovementObserver*> observers_;
  public:
    void registerPlayerMovementObserver(PlayerMovementObserver &observer);
    void unregisterPlayerMovementObserver(PlayerMovementObserver &observer);
    void notifyPlayerMovementObservers(glm::ivec2 &delta);

    virtual void playerRegisterNotification(PlayerMovementSubject &player) = 0;
    virtual void playerUnregisterNotification(PlayerMovementSubject &player) = 0;
};


#endif //GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
