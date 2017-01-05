#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <ostream>

#include "Types.h"
#include "PlayerMovementSubjectObserver.h"

class Player : public PlayerMovementSubject, public PlayerMovementObserver
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constants
  public:
    static const int RANGE = 25;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    Player();
    Player(Position position, Direction direction);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    inline const Position &getPosition(void) const{return position_;}
    inline const Direction &getDirection(void) const{return direction_;}
    inline size_t getId() const{return id_;}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    void move(Vec2i delta);
    friend std::ostream &operator<<(std::ostream &stream, const Player &rhs);

    virtual void playerRegisterNotification(PlayerMovementSubject &player);
    virtual void playerUnregisterNotification(PlayerMovementSubject &player);
    virtual void playerMovementNotification(PlayerMovementSubject &player, Distance &delta);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    size_t id_;
    Position position_;
    Direction direction_;
    static size_t object_counter_;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
