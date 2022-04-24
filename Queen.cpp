#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position\
& end) const {
    //Allowing for vertical and horizontal movement
  
       //ROOK-LIKE MOVEMENTS
       //Vertical
       if (start.first == end.first) {
           return true
       }
       //Horizontal
       if (start.second == end.second) {
           return true;
       }
 
       //BISHOP LIKE MOVEMENTS
       //Diagonal
       for (int i = 1; i < 7; i++) {
           if ((end.first == start.first + i || end.first == start.first - i) && (end.second == start.second + i || end.second == start.second + i)) {
               return true;
           }
       }
 
   }                                      
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
