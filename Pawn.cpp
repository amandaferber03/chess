#include "Pawn.h"

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////                                         
    // [REPLACE THIS STUB] //                                         
    /////////////////////////                                         
    bool white_turn_first = is_white() && start.second == 2;
    bool black_turn_first = !(is_white()) && start.second == 7;

    if(start.first == end.first) {
      if(white_turn_first) {
	if(start.second == end.second + 1 || start.second == end.second + 2) {
	  return true;
	}
      }
      else if(is_white()) {
	if(start.second == end.second + 1) {
	  return true;
	}
      }
      else if(black_turn_first) {
	if(end.second == start.second - 1 || end.second == start.second -2) {
	  return true;
	}
      }
      else{//if black
	if(end.second == start.second - 1) {
	  return true;
	}
      }
    }
    return false;

    // checks if start and end Position are within the bounds of the board
    
    // checks if the player moved Pawn the correct way (1 space forward)

  }
}
