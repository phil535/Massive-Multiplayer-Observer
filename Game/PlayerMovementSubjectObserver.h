#ifndef GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
#define GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H

#include <unordered_set>

class PlayerMovementObserver
{
  public:
    void notify();
};

class PlayerMovementSubject
{
    std::unordered_set<PlayerMovementObserver*> observers_;
  public:
    void registerPlayerMovementObserver(PlayerMovementObserver *observer);
    void unregisterPlayerMovementObserver(PlayerMovementObserver *observer);
    void notifyPlayerMovementObservers();
};


#endif //GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
