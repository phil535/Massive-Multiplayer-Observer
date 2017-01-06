#ifndef GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
#define GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H

#include "Types.h"
#include <unordered_set>

class Player;

class PlayerMovementObserver
{
    friend class PlayerMovementSubject;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Enumerations
  public:
    enum REGISTER_RESULT
    {
      NEW_PLAYER,
      ALREADY_EXISTS
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    PlayerMovementObserver(Player &player);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    inline Player &getPlayer(){return player_;};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    virtual void playerMovementNotification(Player &player, Distance &delta) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    Player &player_;
};

class PlayerMovementSubject
{
    friend class PlayerMovementObserver;

  public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
    PlayerMovementSubject(Player &player);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    PlayerMovementObserver::REGISTER_RESULT registerPlayerMovementObserver(PlayerMovementObserver &observer);
    void unregisterPlayerMovementObserver(PlayerMovementObserver &observer);
    void notifyPlayerMovementObservers(Distance &delta);

    virtual void playerRegisterNotification(Player &player) = 0;
    virtual void playerUnregisterNotification(Player &player) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    inline Player &getPlayer(){return player_;};
    inline std::unordered_set<PlayerMovementObserver*> &getObservers(){return observers_;}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    Player &player_;
    std::unordered_set<PlayerMovementObserver*> observers_;
};


#endif //GAME_PLAYERMOVEMENTSUBJECTOBSERVER_H
