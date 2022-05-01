#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
  
        // vertical movement
        if (start.first == end.first) {
                return true;
        }
        // horizontal movement
        if (start.second == end.second) {
            return true;
        }
 
        // diagonal movement
        for (int i = 1; i < 7; i++) {
            if ((end.first == start.first + i || end.first == start.first - i) && (end.second == start.second + i || end.second == start.second - i)) {
                return true;
            }
        }                                      
        return false;
    }

}
