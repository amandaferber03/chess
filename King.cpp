#include "King.h"

namespace Chess
{

  bool King::legal_move_shape(const Position& start, const Position& end) const {
   
   // horizontal movement
   if (start.second == end.second) {
     if (end.first == start.first + 1 || end.first == start.first - 1) {
       return true;
     }
   }
   // vertical movement
   if (start.first == end.first) {
     if (end.second == start.second + 1 || end.second == start.second - 1) {
       return true;
     }
   }
   // diagonal movement
   if (end.first == start.first + 1 || end.first == start.first - 1) {
     if (end.second == start.second + 1 || end.second == start.second - 1) {
       return true;
     }
   }

   return false;

  }

}
