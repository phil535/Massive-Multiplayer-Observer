
#include "Position.h"
#include "Game.h"

/*--------------------------------------------------------------------------------------------------------------------*/
Position::Position(void)
    :pos_x_(0), pos_y_(0)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
Position::Position(const int & pos_x, const int & pos_y)
    :pos_x_(pos_x), pos_y_(pos_y)
{}

/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream &operator<<(std::ostream &stream, const Position &rhs)
{
  stream << "(" << rhs.pos_x_ << "," << rhs.pos_y_ << ")";
  return stream;
}
