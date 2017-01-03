#ifndef MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
#define MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H

#include <ostream>
#include "Position.h"

class Player
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor / Deconstructor
  public:
    Player();
    Player(const int & pos_x, const int & pos_y);
    Player(const int & pos_x, const int & pos_y, const int & dir_x, const int & dir_y);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    const Position &getPosition(void) const
    { return position_; }
    const Position &getDirection(void) const
    { return direction_; }
    inline size_t getId() const
    { return id_; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Methods
    void move(void);
    friend std::ostream &operator<<(std::ostream &stream, const Player &rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member
  private:
    size_t id_;
    Position position_;
    Position direction_;
    static size_t object_counter_;
};

#endif //MASSIVE_MULTIPLAYER_OBSERVER_PLAYER_H
