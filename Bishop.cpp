#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    return false;
  }

  char to_ascii() const {
    if(is_white()) {
      return 'B';
    }
    else {
      return 'b';
    }
  }

  std::string to_unicode() const {
    if(is_white()) {
      return "U+2657";
    }
    else {
      return "U+265D";
    }
  }
}
