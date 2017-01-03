
#ifndef  MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H
#define  MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H

#include <ostream>

class Position
{
  public:

    Position(void);

    Position(const int & pos_x, const int & pos_y);

    const int &getX() const
    { return pos_x_; }

    const int &getY() const
    { return pos_y_; }

    friend std::ostream &operator<<(std::ostream &stream, const Position &rhs);

  private:

    int pos_x_;
    int pos_y_;
};
#endif // MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H
