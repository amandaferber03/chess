#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////                                         
    // [REPLACE THIS STUB] //                                         
    /////////////////////////                                         
    return false;
  }

  char to_ascii() const {
    if(is_white()) {
      return 'K';
    }
    else {
      return 'k';
    }
  }

  std::string to_unicode() const {
    if(is_white()) {
      return "U+2654";
    }
    else {
      return "U+265A";
    }
  }
}
