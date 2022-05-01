#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    for (int i = 1; i <= 7; i++) {
       if ((end.first == start.first + i || end.first == start.first - i) && (end.second == start.second + i || end.second == start.second - i)) {
           return true;
       }
   	}
   	return false;
  }
}
