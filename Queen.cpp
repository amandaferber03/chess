#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position\
& end) const {
    /////////////////////////                                         
    // [REPLACE THIS STUB] //                                         
    /////////////////////////                                         
    return false;
  }
  char to_ascii() const {
    if(is_white()) {
      return 'Q';
    }
    else {
      return 'q';
    }
  }

  std::string to_unicode() const {
    if(is_white()) {
      return "U+2655";
    }
    else {
      return "U+265B";
    }
  }
}
