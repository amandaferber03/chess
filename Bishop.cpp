#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    for (int i = 1; i <= 7; i++) {
       if ((end.first == start.first + i || end.first == start.first - i) && (end.second == start.second + i || end.second == start.second + i)) {
           return true;
       }
   	}
   	return false;
 	}
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
