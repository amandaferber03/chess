#include "Pawn.h"

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////                                         
    // [REPLACE THIS STUB] //                                         
    /////////////////////////                                         

    // if start == Position in map
    // if Board::occ[start] == Pawn

    // checks if start and end Position are within the bounds of the board
    
    // checks if the player moved Pawn the correct way (1 space forward)
    if (start.first == end.first && end.second == start.second + 1) {
        return true
      // }
    // }
    else {
      // return false
    // }


    }
    return false;
  }
}