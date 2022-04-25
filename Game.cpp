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


	void Game::queen_path_clear(const Position& start, const Position& end) {

		// check if diagonal path is clear
		return bishop_path_clear(const Position& start, const Position& end);

		// check if horizontal path is clear


		// check if vertical path is clear

	}

	void Game::make_move(const Position& start, const Position& end) {

		bool path_clear = true;
		bool make_move = true;

		// checks if piece exists at starting position 
		if (board(start) == nullptr) {
			throw Exception("no piece at start position");
		}

		// checks if start and end positions are the same
		if (start.first == end.first && start.second == end.second) {
			throw Exception("illegal move shape");
		}

		Piece * piece = board(start);
		char piece_type = piece.to_ascii();
		
		/*
		if (piece_type == 'P' || piece_type == 'p') {
		  if(board(end) == nullptr) {
		    make_move = piece.legal_move_shape();
		  }
		  else {
		    make_move =	piece.legal_capture_shape();
		    if(make_move) {
		      board.get_occ().erase(end);
		    }
		  }
		}
		*/

		// for Knight and King, don't need to check if path is clear

		else if(piece.legal_move_shape()) {
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
			}
		}
		    
		
		 		  
		// if statements to call helper functions that check if path is
		// clear for a certain piece

		// check if path is clear
		// if path is not clear, make_move = false




		// makes the move if make_move = true



		// include error handling if valid_positions == false
		// call these functions:
		// legal_move_position
		// legal_capture_position
			// update point value
			// create a field representing point value? how do we store the point value of each player?
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
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
        return -1;
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
