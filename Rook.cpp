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

  char to_ascii() const {
    if(is_white()) {
      return 'R';
    }
    else {
      return 'r';
    }
  }

  std::string to_unicode() const {
    if(is_white()) {
      return "U+2656";
    }
    else {
      return "U+265C";
    }
  }
}
