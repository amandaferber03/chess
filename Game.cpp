#include <cassert>
#include "Game.h"
#include <stdlib.h>//abs() for make_move function
#include <string>
#include <cctype> // toupper
#include <iostream> // toupper

using std::string;

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
	bool Game::rook_path_clear(const Position& start, const Position& end) {
		char row = start.second + 1;
		char col = start.first + 1;

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
			return true;
	}

	bool Game::pawn_path_clear(const Position& start) {
		
		char row = start.second + 1;
		Position pos = std::make_pair(start.first, row);

		if (board(pos) != nullptr) {
			return false;
		}
		return true;
	}

	bool Game::bishop_path_clear(const Position& start, const Position& end) {
		
		int num_spaces = abs(end.second - start.second);
		int row = start.second;
		int col = start.first;

		std::map<Position, Piece *> board_occ = board.get_occ();

		for (int i = 1; i < num_spaces; i++) {
			// upwards movement
			if (end.second - start.second > 0) {
				// up-right movement
				if (end.first - start.first > 0) {
					Position pos = std::make_pair(col + num_spaces, row + num_spaces);
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
				// up-left movement
				else {
					Position pos = std::make_pair(col - num_spaces, row + num_spaces);
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
			}
			// downwards movement
			else {
				// down-right movement
				if (end.first - start.first > 0) {
				  Position pos = std::make_pair(col + num_spaces, row - num_spaces);
				  if (board_occ[pos] != nullptr) {
						return false;
					}
				}
				// down-left movement
				else {
					Position pos = std::make_pair(col - num_spaces, row - num_spaces);
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
			}
		}
		return true;
	}

	bool Game::queen_path_clear(const Position& start, const Position& end) {
          // check if diagonal path is clear
	  int diag_col = abs(end.first - start.first);
	  int diag_row = abs(end.second - start.second);

	  if(diag_col == diag_row) {
	    return bishop_path_clear(start, end);
	  }
	  else {//check if horizontal or vertical path is clear
	    return rook_path_clear(start, end);
	  }
	}

        bool Game::mystery_path_clear(const Position& start, const Position& end) {
          // check if diagonal path is clear                                                                                                   
          int diag_col = abs(end.first - start.first);
          int diag_row = abs(end.second - start.second);

	  bool vertical = start.first == end.first;
	  bool horizontal = start.second == end.second;

          if(diag_col == diag_row) {
            return bishop_path_clear(start, end);
          }
          else if (vertical || horizontal) {//check if horizontal or vertical path is clear                                                   
            return rook_path_clear(start, end);
          }
	  else {
	    return true;
	  }
        }

        bool Game::legal_move_path(const Position& start, const Position& end) {
                const Piece * piece = board(start);
                char piece_type = piece->to_ascii();
		bool path_clear = true;

		// checks if path is clear (except for Knight and King) if move shape or capture shape is legal
		if (piece->legal_move_shape(start, end) || piece->legal_capture_shape(start, end)) {
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
		return path_clear;
    }

	void check_positions(const Position& start, const Position& end) {
	
		bool valid_start = (start.first >= 'A' && start.first <= 'H') && (start.second >= '1' && start.second <= '8');
		if (!valid_start) {
			throw Exception("start position is not on board");
		} 

		bool valid_end = (end.first >= 'A' && end.first <= 'H') && (end.second >= '1' && end.second <= '8');
		if (!valid_end) {
			throw Exception("end position is not on board");	
		}

	}
  
	void Game::make_move(const Position& start, const Position& end) {

		// throws an Exception if start and/or end position(s) are invalid
		check_positions(start, end);

		// checks if piece exists at starting position 
		if (board(start) == nullptr) {
			throw Exception("no piece at start position");
		}

		// checks if start and end positions are the same
		if (start.first == end.first && start.second == end.second) {
		  throw Exception("illegal move shape");
		}

		Piece * piece = board.get_occ().at(start);

		// checks if turn doesn't correspond with right piece color
		if (piece->is_white() != turn_white()) {
			throw Exception("piece color and turn do not match");
		}
		
		bool path_clear = legal_move_path(start, end); 

		// checks if the user is trying to capture the opponent's piece if the path is clear
		if (path_clear) {
		   	if (board(end) != nullptr) {
		    	const Piece * captured_piece = board(end);
		      	if (captured_piece->is_white() == turn_white()) {
					throw std::logic_error("cannot capture own piece");
		    	}
		   	}
		}
		else {
			throw std::logic_error("path is not clear"); 
		}
   
		bool possible_check = exposes_check(start, end);

		// checks if movement exposes check
		if(!possible_check) {// updates pair in map representing end position with
		                    //new piece and deletes key representing piece at start position
		  std::map<Position, Piece *> board_occ = board.get_occ();
		  board_occ[end] = piece;
		  board_occ.erase(start);
		  // TODO: ensure the piece is visually removed from start position
		  //and added to end position using functions in Board.h

		  //should we use the add_piece() function
		  is_white_turn = !is_white_turn;
		}
		else {
		  throw std::logic_error("move exposes check");//CHANGED THIS
		}
	}
		
    bool Game::exposes_check(const Position& start, const Position& end) {
		Game game_replica = *this; 
		game_replica.board.get_occ().at(end) = board.get_occ().at(start); // piece will be at ending position
		game_replica.board.get_occ().erase(start); // piece deleted from starting position

	  	// checks if move causes check to be exposed
	  	if(game_replica.in_check(is_white_turn)) {
	    	return true;
		}
	  	else {
	      	return false;
	  	}
    }

    bool Game::end_of_game(const bool& white) const {
		// variable that represents board
        std::map<Position, Piece*> board_occ = board.get_occ();
		// variable that indicates if player can make legal move to get out of check
	    bool legal_move = false;
        for (std::map<Position, Piece*>::iterator it = board_occ.begin(); it != board_occ.end(); ++it) {
            if (it->second.is_white() == white) {
               	char first_pos = 'A';
               	char second_pos = '0';
               	int counter = 0;
               	for (int i = 0; i < 64; i++) {
					second_pos++; // 1, 2... 6, 7, 8
                	if (counter < 7) {
                  		counter++; // 1, 2... 6, 7
                	}
                	else {
                  		counter = 0;
		  				second_pos = '1';
                  		first_pos++; // B
                	}
                	Position end_pos = std::make_pair(first_pos, second_pos);
                	Game game_replica = *this;
                	try {
                  		game_replica.make_move(it->first, end_pos);
                	}
					// move isn't legal if exception is caught
                	catch (const std::exception& e) {
                  		continue;
                	}
                	legal_move = true;
              	}
            }
        }
        return !legal_move;
  	}

	bool Game::in_check(const bool& white) const {

		// variable to store map
		std::map<Position, Piece*> board_occ = board.get_occ();
	  	Position king_pos;
	  	bool possible_check = false; 

		// iterates through each position in the board and determines position of King
        for (std::map<Position, Piece*>::iterator it = board_occ.begin(); it != board_occ.end(); ++it) {
	    	if (it->second.is_white() == white) {
	      		char piece_type = toupper(it->second.to_ascii());
			}
	      	if (piece_type == 'K') {
				king_pos = it->first;
	      	}
	    }

		// determines if piece could capture king of opposing player
	  	for(std::map<Position, Piece*>::iterator it = board_occ.start(); it != board_occ.end(); ++it) {
			// determines if piece is the opposite color
	    	if (it->second.is_white() != white) {
				// calls legal_move_path of appropriate piece
	      		possible_check = legal_move_path(it->first, king_pos);
	    	}
	  	}
	  	return possible_check;
	}


	bool Game::in_mate(const bool& white) const {
        if (in_check(is_white_turn)) {
	    	return end_of_game(white);
	  	}
	  	else {
	    	return false;
	  	}
	}


	bool Game::in_stalemate(const bool& white) const {
    	if(!in_check(is_white_turn)) {
	    	return end_of_game(white);
	  	}
	  	else {
	    	return false;
	  	}
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
      //TODO: check to see if this is right
      //traverse through the white pieces of the map to see which ones are still there
      int points = 0;
      std::map<Position, Piece*> board_occ = board.get_occ();
      for(std::map<Position, Piece*>::iterator it = board_occ.begin();
	  it != board_occ.end();
	  ++it) {
	if(it->second.is_white() == white) {//if the color of the piece matches whose turn it is
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

		// variable to store map
		std::map<Position, Piece*> board_occ = board.get_occ();

		// attempts to open file
		if (!is.is_open()) {
			throw Exception("Cannot load the game!");
		}

		char piece_symbol;
		char first_pos = 'A';
		char second_pos = '8';
		int counter = 0;

		// captures each character in the file
		while (is >> piece_symbol) {
			if (piece_symbol == 'w') {
				is_white_turn = true;
			}
			else if (piece_symbol == 'b') {
				is_white_turn = false;
			}
			else if (piece_symbol != '-') {
				Position pos = std::make_pair(first_pos, second_pos);
				add_piece(pos, piece_symbol); // TODO: implement function
			}

			// updates position values
			first_pos++; // B, C, D, E, F, G, H
			if (counter < 7) {
				counter++; // 1, 2, 3, 4, 5, 6, 7
			}
			else {
				counter = 0;
				first_pos = 'A';
				second_pos--;
			}
		}

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
