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

	/* Checks if path is clear for Rook movement */
	bool Game::rook_path_clear(const Position& start, const Position& end) const {
	  char row = '0';
	  char col = '0';
	  if(end.second - start.second > 0) {
	    row = start.second + 1;
	  }
	  else {
	    row = start.second - 1;
	  }
	  if(end.first - start.first > 0) {
	    col = start.first + 1;
	  }
	  else {
	    col = start.first - 1;
	  }
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
				  col--;//
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

	/* Checks if path is clear for pawn movement */
	bool Game::pawn_path_clear(const Position& start) const {

        char row = 0;
		char row2 = 0;

		if (is_white_turn) {
			row = start.second + 1;
			row2 = start.second + 2;
		}
		else {
			row = start.second - 1;
			row2 = start.second - 2;
		}
		Position pos = std::make_pair(start.first, row);
		Position pos2 = std::make_pair(start.first, row2);

		//Set of conditionals to determine which boolean to return

		//Pointer not null, there is piece at end and we return false
		if (board(pos) != nullptr) {
			return false;
		}
		else if (board(pos2) != nullptr) {
		  return false;
		}

		//If the pointer is null, path is clear
		return true;
	}

 	 /* Checks if path is clear for bishop movement */
  	bool Game::bishop_path_clear(const Position& start, const Position& end) const {//problem spot
		
		int num_spaces = abs(end.second - start.second);
		int row = start.second;
		int col = start.first;

		std::map<Position, Piece *> board_occ = board.get_occ();

		for (int i = 1; i < num_spaces; i++) {
			// upwards movement
			if (end.second - start.second > 0) {
				// up-right movement
				if (end.first - start.first > 0) {
					Position pos = std::make_pair(col + i, row + i);//made change here
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
				// up-left movement
				else {
					Position pos = std::make_pair(col - i, row + i);//made change here
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
			}
			// downwards movement
			else {
				// down-right movement
				if (end.first - start.first > 0) {
				  Position pos = std::make_pair(col + i, row - i);//made change here
				  if (board_occ[pos] != nullptr) {
						return false;
					}
				}
				// down-left movement
				else {
					Position pos = std::make_pair(col - i, row - i);//made change here
					if (board_occ[pos] != nullptr) {
						return false;
					}
				}
			}
		}
		return true;
	}

	/* Checks if path is clear for queen movement */
	bool Game::queen_path_clear(const Position& start, const Position& end) const {
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

        bool Game::mystery_path_clear(const Position& start, const Position& end) const {
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


/* In the midst of an ongoing game, checks for the respective piece's possible paths using the individual
 * piece's path_clear functions
 */	
  bool Game::legal_move_path(const Position& start, const Position& end) const {
    Piece * piece = board.get_occ().at(start);
                char piece_type = piece->to_ascii();
		bool path_clear = true;
		

		// checks if path is clear (except for Knight and King) if move shape or capture shape is legal
		if (piece->legal_move_shape(start, end)) {
			switch (piece_type) {
				//Rook
				case 'R':
				case 'r': 
					path_clear = rook_path_clear(start, end);
		    		break;
				//Bishop	
				case 'B':
				case 'b':
					path_clear = bishop_path_clear(start, end);
		    		break;
				//Queen	
				case 'Q':
		  		case 'q': 
				  	path_clear = queen_path_clear(start, end);
		    		break;
				//Pawn	
				case 'P':
				case 'p':
				  if (board(end) != nullptr) {
                    throw Exception("illegal capture shape");
				  }
				  if (is_white_turn) {
					if (end.second == start.second + 2) {
						path_clear = pawn_path_clear(start);
					}
			          }
				  else {
				    if (end.second == start.second - 2) { 
				      path_clear = pawn_path_clear(start);
				    }
				  }		     
				  break;
				//Mystery piece  
			    case 'M':
			    case 'm':
				    path_clear = mystery_path_clear(start, end);
			    default: break;
			}
		}

		//Calling for path_clear
		else if (piece->legal_capture_shape(start, end) && board(end) != nullptr) {
		  return path_clear;
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

	/*Function that helps verify if a given position is in the board */
    void Game::check_positions(const Position& start, const Position& end) {
	
		bool valid_start = (start.first >= 'A' && start.first <= 'H') && (start.second >= '1' && start.second <= '8');
		if (!valid_start) {
			throw Exception("start position is not on board");
		} 

		bool valid_end = (end.first >= 'A' && end.first <= 'H') && (end.second >= '1' && end.second <= '8');
		if (!valid_end) {
			throw Exception("end position is not on board");	
		}

	}
  
  	/* Given start and end positions, we change the piece's position in the board */
 	void Game::make_move(const Position& start, const Position& end, bool change_pos) {
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
		char ascii_char = piece->to_ascii();
		// checks if turn doesn't correspond with right piece color
		if (piece->is_white() != turn_white()) {
			throw Exception("piece color and turn do not match");
		}
		bool path_clear = legal_move_path(start, end); 
		// checks if the user is trying to capture the opponent's piece if the path is clear
		if (path_clear) {
		   	if (board(end) != nullptr) {
		    	Piece * captured_piece = board.get_occ().at(end);
		      	if (captured_piece->is_white() == turn_white()) {
					throw std::logic_error("cannot capture own piece");
		    	}
				else {
			    	//delete captured_piece;
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
		  if(!change_pos) {
		    return;
		  }
		   board.change_pos(start, end, piece, ascii_char);
		  // TODO: ensure the piece is visually removed from start position
		  //and added to end position using functions in Board.h

		  //should we use the add_piece() function
		  is_white_turn = !is_white_turn;

		}
		else {
		  throw std::logic_error("move exposes check");//CHANGED THIS
		}
	}
		
	/* Verifies whether or not a movement exposes a check situation */	
    bool Game::exposes_check(const Position& start, const Position& end) {
		Game game_replica = *this;
		Piece * piece = board.get_occ().at(start);
		char ascii_char	= piece->to_ascii();
        Piece * another_piece = game_replica.board.change_map(start, end, piece, ascii_char);
		
	  	// checks if move causes check to be exposed
	  	if(game_replica.in_check(is_white_turn)) {
			if ((ascii_char == 'p' && end.second == '1') || (ascii_char == 'P' && end.second == '8')) {
				delete another_piece;
			}
	    	return true;
		}
	  	else {
			if ((ascii_char == 'p' && end.second == '1') || (ascii_char == 'P' && end.second == '8')) {
				delete another_piece;
			}
	      	return false;
	  	}
    }

	/* Bool function that helps us determine if a game has ended or not */
    bool Game::end_of_game(const bool& white) const {
		// variable that represents board
        std::map<Position, Piece*> board_occ = board.get_occ();
		// variable that indicates if player can make legal move to get out of check
	    bool legal_move = false;
		Game game_rep = *this;
        for (std::map<Position, Piece*>::iterator it = board_occ.begin(); it != board_occ.end(); ++it) {
            if (it->second->is_white() == white) {
               	char first_pos = 'A';
               	char second_pos = '8';
				int row_num = 8;
               	int counter = 7;
               	for (int i = 0; i < 64; i++) {
					Position end_pos = std::make_pair(first_pos, second_pos);

					if (i == counter && i > 0) {
						row_num--;
						second_pos--;
						first_pos = 'A';
						counter+=8;
					}
					else {
						first_pos++;
					}

                	try {
			  game_rep.make_move(it->first, end_pos, false);
                	}
					// move isn't legal if exception is caught
                	catch (const std::exception& e) {
                  		continue;
                	}					
                	return false;
              	}
            }
        }
        return !legal_move;
  	}

		/* If a designated player is in check, this function will return true */
		bool Game::in_check(const bool& white) const {
			// variable to store map
			std::map<Position, Piece*> board_occ = board.get_occ();
	  		Position king_pos;
	  		bool possible_check = false; 

			// iterates through each position in the board and determines position of King
       	 for (std::map<Position, Piece*>::iterator it = board_occ.begin(); it != board_occ.end(); ++it) {
	    		if (it->second->is_white() == white) {
		  			char piece_type = toupper(it->second->to_ascii());
	      		  	if (piece_type == 'K') {
		    			king_pos = it->first;
	   		   	   }
	       		}
			}

			// determines if piece could capture king of opposing player
	  		for(std::map<Position, Piece*>::iterator inner_it = board_occ.begin(); inner_it != board_occ.end(); ++inner_it) {
				// determines if piece is the opposite color
	    		if (inner_it->second->is_white() != white) {
					// calls legal_move_path of appropriate piece
			  		Position start_pos = inner_it->first;
			  		try {
			    		possible_check = legal_move_path(start_pos, king_pos);
		  			}
		  			catch(const std::exception& e) {
		    			continue;
			  		}
				}
			}
			return possible_check;
		}	

	/* Function that returns true if the designated player is in mate */
	bool Game::in_mate(const bool& white) const {
    	if (in_check(is_white_turn)) {
		    return end_of_game(white);
	  	}
		else {
		    return false;
	  	}
	}

	/* Checks to see if a player is or is not in a stalement position */
	bool Game::in_stalemate(const bool& white) const {
		if(!(in_check(is_white_turn))) {
		    return end_of_game(white);
		}
		else {
		    return false;
		}
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {                                                                     
      //traverse through the white pieces of the map to see which ones are still there                             
      int points = 0;
      std::map<Position, Piece*> board_occ = board.get_occ();
      for(std::map<Position, Piece*>::iterator it = board_occ.begin();
          it != board_occ.end();
          ++it) {
        if(it->second->is_white() == white) {//if the color of the piece matches whose turn it is                  
          points += it->second->point_value();
        }
      }
      return points;
    }


    std::istream& operator>> (std::istream& is, Game& game) {
		game.board.erase_if_existing();
		string valid_piece_designators = "-KkQqBbNnRrPpMmw";
		std::map<Position, Piece*> board_occ = game.board.get_occ();
		
		char piece_symbol;
		char first_pos = 'A';
		char second_pos = '8';
		int i = 0;
		int counter = 0;
		bool valid_symbol = false;
		
		while (is >> piece_symbol) {
			Position pos = std::make_pair(first_pos, second_pos);
			for (size_t i = 0; i < valid_piece_designators.length(); i++) {
				if (piece_symbol == valid_piece_designators.at(i)) {
					valid_symbol = true;
					break;
					}
			}
			
			if (!valid_symbol) {
				throw Exception("Cannot load the game!");
			}

            // determines current turn
            if (piece_symbol == 'b' && i == 64) {
				game.is_white_turn = false;
			}
			else if (piece_symbol == 'w') {
				game.is_white_turn = true;
				}
            // adds piece to board
            else if (piece_symbol != '-') {
				game.board.add_piece(pos, piece_symbol);
			}

            // updates position
            first_pos++;
			if (counter < 7) {
				counter++;
			}
			else {
				counter = 0;
				first_pos = 'A';
				second_pos--;
			}
			i++;
		}

		return is;
	}

	void Game::erase_board() {
    	board.erase_if_existing();
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
