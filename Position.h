
#ifndef  MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H
#define  MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H

class Position
{
  public:

    Position(void);

    Position(const int & pos_x, const int & pos_y);

    const int & getX() {return pos_x_;}
    const int & getY() {return pos_y_;}

  private:

    int pos_x_;
    int pos_y_;
};
#endif // MASSIVE_MULTIPLAYER_OBSERVER_POSITION_H
