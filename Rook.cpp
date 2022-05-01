#include "Rook.h"

namespace Chess
{

/* Verifies if the move made by the rook is within the game's parameters and standards	*/
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {

    // MAY NOT MOVE THROUGH OTHER PIECES

    // movement along vertical line
    if (start.first == end.first) {
      return true;
    }

    // movement along horizontal line
    if (start.second == end.second) {
      return true;
    }

    return false;
  }

}
