#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <ostream>

#include "Types.h"
#include "PlayerMovementSubjectObserver.h"

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
    Player(Game &game, Position position, Direction direction);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    inline const Position &getPosition(void) const{return position_;}
    inline const Direction &getDirection(void) const{return direction_;}
    inline size_t getId() const{return id_;}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    bool isInRangeOf(Player &player) const;
    void move(Vec2i delta);
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
    Direction direction_;
    static size_t object_counter_;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
