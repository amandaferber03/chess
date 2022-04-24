#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    //Horizontal and diagonal movement
   	if (end.second == start.second + 1 || end.second == start.second - 1) {
       //Allowing for horizontal movement
       if (end.first == second.first) {
           return true;
       }
       //Allowing for diagonal movement
       if (end.first == second.first + 1 || end.first == second.first - 1) {
           return true;
       }
   }
 
   //Vertical movement
   if (end.first == start.first + 1 || end.first == start.first - 1) {
       //Making sure it is within the same line
       if (end.second == second.second) {
           return true;
       }
   }
 
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
