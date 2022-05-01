#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

	  // vertical L
	  if (end.first == start.first + 1 || end.first == start.first - 1) {
		  if (end.second == start.second + 2 || end.second == start.second - 2) {
			  return true;
		  }
	  }
	
    // horizontal L
    if (end.second == start.second + 1 || end.second == start.second - 1) {
      if (end.first == start.first + 2 || end.first == start.first - 2) {
        return true;
      }
    }
    return false;
  }

}
