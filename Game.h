#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

	class Game {

	public:
		// This default constructor initializes a board with the standard
		// piece positions, and sets the state to white's turn
		Game();

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Displays the game by printing it to stdout
		void display() const { board.display(); }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Checks if path is clear for Rook movement
		bool  rook_path_clear(const Position& start, const Position& end) const;

		// Checks if path is clear for Pawn movement
		bool pawn_path_clear(const Position& start) const;

		// Checks if path is clear for Bishop movement
		bool bishop_path_clear(const Position& start, const Position& end) const;
	    
		//Checks if path is clear for Queen movement
	    bool queen_path_clear(const Position& start, const Position& end) const;
	    
		//Checks if path is clear for Mystery movement
	    bool mystery_path_clear(const Position& start, const Position& end) const;
	    
		//Checks if a move exposes check
	    bool exposes_check(const Position& start, const Position& end);
	    
		//checks if a move shape is legal and a path is clear
	  bool legal_move_path(const Position& start, const Position& end) const;
	    
		// Checks if position specified by user is valud
		void check_positions(const Position& start, const Position& end);

		// the turn is switched white <-> black. Otherwise, an exception is thrown
	  void make_move(const Position& start, const Position& end, bool change_pos);
    
		//Verifies if the game has ended or not
	    bool end_of_game(const bool& white) const;
	  
		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if the designated player is in stalemate
		bool in_stalemate(const bool& white) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

		void erase_board();

	private:
		// The board
		Board board;

		// Is it white's turn?
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);

        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
