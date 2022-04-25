#include <cassert>
#include "Game.h"
#include <stdlib.h>//abs() for make_move function

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	// checks if path is clear for Rook movement
	void Game::rook_path_clear(const Position& start, const Position& end) {

		char row = start.second + 1;
		char col = start.first + 1;

		while (path_clear) {
			// checks for pieces in horizontal path
			// will not execute if path is vertical
			for (int i = 0; i < abs(end.first - start.first) - 1; i++) {
				Position pos = std::make_pair(col, start.second);
				if (board(pos) != nullptr) {
					return false;
				}
				// incrementing row
				if (end.first - start.first > 0) {
					col++;
				}
				else {
					col--;
				}
			}
			// checks for pieces in vertical path
			// will not execute if path is horizontal
			for (int i = 0; i < abs(end.second - start.second) - 1; i++) {
				Position pos = std::make_pair(start.first, row);
				if (board(pos) != nullptr) {
					return false;
				}
				// incrementing col
				if (end.second - start.second > 0) {
					row++;
				}
				else {
					row--;
				}
			}
		}
	}

	void Game::pawn_path_clear(const Position& start) {
		
		char row = start.second + 1;
		Position pos = std::make_pair(start.first, row);

		if (board(pos) != nullptr) {
			return false;
		}
	}

	bool Game::bishop_path_clear(const Position& start, const Position& end) {
		
		int num_spaces = abs(end.second - start.second);
		int row = start.second;
		int col = start.first;

		for (int i = 1; i < num_spaces; i++) {
			// upwards movement
			if (end.second - start.second > 0) {
				// up-right movement
				if (end.first - start.first > 0) {
					Position pos = std::make_pair(col + num_spaces, row + num_spaces);
					if (pos != nullptr) {
						return false;
					}
				}
				// up-left movement
				else {
					Position pos = std::make_pair(col - num_spaces, row + num_spaces);
					if (pos != nullptr) {
						return false;
					}
				}
			}
			// downwards movement
			else {
				// down-right movement
				if (end.first - start.first > 0) {
					Position pos = std:make_pair(col + num_spaces, row - num_spaces);
					if (pos != nullptr) {
						return false;
					}
				}
				// down-left movement
				else {
					Position pos = std::make_pair(col - num_spaces, row - num_spaces);
					if (pos != nullptr) {
						return false;
					}
				}
			}
    	}
	}


	bool Game::queen_path_clear(const Position& start, const Position& end) {
          // check if diagonal path is clear
	  int diag_col = abs(end.first - start.first);
	  int diag_row = abs(end.second - start.second);

	  if(diag_col == diag_row) {
	    return bishop_path_clear(const Position& start, const Position& end);
	  }
	  else {//check if horizontal or vertical path is clear
	    return rook_path_clear(const Position& start, const Position& end);
	  }
	}

        bool Game::mystery_path_clear(const Position& start, const Position& end) {
          // check if diagonal path is clear                                                                                                   
          int diag_col = abs(end.first - start.first);
          int diag_row = abs(end.second - start.second);

	  bool vertical = start.first == end.first;
	  bool horizontal = start.second == end.second;

          if(diag_col == diag_row) {
            return bishop_path_clear(const Position& start, const Position& end);
          }
          else if (vertical || horizontal) {//check if horizontal or vertical path is clear                                                   
            return rook_path_clear(const Position& start, const Position& end);
          }
	  else {
	    return true;
	  }
        }

	void Game::make_move(const Position& start, const Position& end) {

		// checks if piece exists at starting position 
		if (board(start) == nullptr) {
			throw Exception("no piece at start position");
		}

		// checks if start and end positions are the same
		if (start.first == end.first && start.second == end.second) {
			throw Exception("illegal move shape");
		}

		Piece * piece = board(start);

		// checks if turn doesn't correspond with right piece color
		if (piece.is_white() != turn_white()) {
			throw Exception("piece color and turn do not match");
		}
		
		char piece_type = piece.to_ascii();
		bool path_clear = true;

		// checks if path is clear (except for Knight and King) if move shape or capture shape is legal
		if (piece.legal_move_shape() || piece.legal_capture_shape()) {
			switch (piece_type) {
				case 'R':
				case 'r': 
					path_clear = rook_path_clear(start, end);
		    		break;
				case 'B':
				case 'b':
					path_clear = bishop_path_clear(start, end);
		    		break;
				case 'Q':
		  		case 'q': 
				  	path_clear = queen_path_clear(start, end);
		    		break;
				case 'P':
				case 'p': 
					if (end.first == start.first + 2) {
						path_clear = pawn_path_clear(start);
					}
					break;
			    case 'M':
			    case 'm':
				    path_clear = mystery_path_clear(start, end);
			    default: break;
			}
		}
		// piece does not exist at end position
		else if (board(end) != nullptr){
			throw Exception("illegal capture shape");
		}
		else {
			throw Exception("illegal move shape");
		}

		// checks if the user is trying to capture the opponent's piece if the path is clear
		if (path_clear) {
		  	if (board(end) != nullptr) {
		    	Piece * captured_piece = board(end);
		    	if (captured_piece.is_white() == turn_white()) {
					throw Exception("cannot capture own piece");
		    	}
		  	}
		}
		else {
		  	throw Exception("path is not clear"); 
		}
   
		bool exposes_check = exposes_check(start, end);

		// checks if movement exposes check
		if(!exposes_check) {
			// updates pair in map representing end position with new piece and deletes key representing piece at start position
			board.get_occ()[end] = piece;
			board.get_occ().erase(start);

			// TODO: ensure the piece is visually removed from start position and added to end position using functions in Board.h
		  

		  //should we use the add_piece() function
		  is_white_turn = !is_white_turn;
		  return true;
		}
		else {
		  throw Exception("move exposes check");
		}
	}
		
        bool Game::exposes_check(const Position& start, const Position& end) {
	  //TODO: Implement this function
        }
	bool Game::in_check(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}


	bool Game::in_mate(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}


	bool Game::in_stalemate(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
      //TODO: check to see if this is right
      //traverse through the white pieces of the map to see which ones are still there
      int points = 0;
      std::map<Position, Piece*> board_occ = board.get_occ();
      for(std::map<Position, Piece*>::iterator it = board_occ.start();
	  it != board_occ_end();
	  ++it) {
	if(it->second.is_white() == white) {
	  char piece_type = toupper(it->second.to_ascii());//TODO: do we need to #include something special for this
	  switch (piece_type) {
	  case 'P': points += 1;
	  case 'N': points += 3;
	  case 'B': points += 3;
	  case 'R': points += 5;
	  case 'Q': points += 9;
	  case 'M': points += it->second.point_value();
	  default: break;
	  }
	}
      }
      return points;
    }


      std::istream& operator>> (std::istream& is, Game& game) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
