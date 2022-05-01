#include "Pawn.h"
#include <iostream>
#include <string>
namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const{

    bool white_turn_first = is_white() && start.second == '2';
    bool black_turn_first = !is_white() && start.second == '7';

    if (start.first == end.first) {

      // pawn may move one or two spaces forward on first move
      if (white_turn_first) {
	      if (end.second == start.second + 1 || end.second == start.second + 2) {
	        return true;
	      }
      }
      // pawn may only move one space on subsequent moves
      else if (is_white()) {
	      if (end.second == start.second + 1) {
	        return true;
      	}
      }
      else if (black_turn_first) {
	      if (end.second == start.second - 1 || end.second == start.second - 2) {
	        return true;
	      }
      }
      else { // black's turn but not first turn
	      if (end.second == start.second - 1) {
	        return true;
	      }
      }
    }
    return false;
  }

  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
		
    // white piece
    if (is_white()) {
      if ((end.first == start.first + 1 || end.first == start.first - 1) && (end.second == start.second + 1)) {
        return true;
      }
    }
    // black piece
    else {
      if ((end.first == start.first - 1 || end.first == start.first + 1) && (end.second == start.second - 1)) {
        return true;
      }
    }

    return false;
  }
   
}
