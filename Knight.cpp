#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

	  // vertical L
	  if (end.first = start.first + 1 || end.first = start.first - 1) {
		  if (end.second = start.second + 2 || end.second = start.second - 2) {
			  return true;
		  }
	  }
	
    // horizontal L
    if (end.second = start.second + 1 || end.second = start.second - 1) {
      if (end.first = start.first + 2 || end.second = start.first - 2) {
        return true;
      }
    }
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
