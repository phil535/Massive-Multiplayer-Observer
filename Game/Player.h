#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <ostream>
#include <memory>

#include "Types.h"
#include "PlayerMovementSubjectObserver.h"
#include "MovementPattern.h"

class Game;

class Player : public PlayerMovementSubject, public PlayerMovementObserver
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constants
  public:
    static const int RANGE = 100;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    Player(Game &game);
    Player(Game &game, Position position);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    inline Position &getPosition(void){return position_;}
    inline size_t getId() const{return id_;}
    inline Game &getGame(){return game_;};
    void setStrategy(std::unique_ptr<MovementPattern> strategy);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    bool isInRangeOf(Player &player) const;
    void move();

    friend std::ostream &operator<<(std::ostream &stream, const Player &rhs);

    virtual void playerRegisterNotification(Player &player);
    virtual void playerUnregisterNotification(Player &player);
    virtual void playerMovementNotification(Player &player, Distance &delta);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    Game &game_;
    size_t id_;
    Position position_;
    static size_t object_counter_;
    std::unique_ptr<MovementPattern> movement_strategy_;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
