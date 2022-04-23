#include "Rook.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {

    // MAY NOT MOVE THROUGH OTHER PIECES

    // movement along vertical line
    if (start.first == end.first) {
      return true
    }

    // movement along horizontal line
    if (start.second == end.second) {
      return true;
    }

    return false;
  }
}
