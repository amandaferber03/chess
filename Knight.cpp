#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    // Moves in an L-shape either 2-by-1 or 1-by-2
    // Only piece that can move through other pieces

    

    return false;
  }

  char to_ascii() const {
    if(is_white()) {
      return 'N';
    }
    else {
      return 'n';
    }
  }

  std::string to_unicode() const {
    if(is_white()) {
      return "U+2658";
    }
    else {
      return "U+265E";
    }
  }
}
