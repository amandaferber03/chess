#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  const Piece* Board::operator()(const Position& position) const {
    auto it = occ.find(position);
    if (it == occ.end()) {
      return NULL;
    }

    return occ.at(position);
  }

  void Board::erase_if_existing() {
	  for (std::map<Position, Piece*>::iterator it = occ.begin(); it != occ.end(); ++it) {
	    delete it->second;
	    //occ.erase(it->first);
	  }
	  occ.clear();
  }

  Board::~Board() { }

  void Board::add_piece(const Position& position, const char& piece_designator) {

    string valid_piece_designators = "KkQqBbNnRrPpMm";
    bool valid_designator = false;
    bool valid_position = false;
    bool piece_exists = false;

    // updates valid_designator if applicable
    for (size_t i = 0; i < valid_piece_designators.length(); i++) {
      if (piece_designator == valid_piece_designators.at(i)) {
        valid_designator = true;
        break;
      }
    }

    // updates valid_position if applicable
    if ((position.first >= 'A' && position.first <= 'H') && (position.second >= '1' && position.second <= '8')) {
      valid_position = true;
    }


    // updates no_piece_exists if applicable
    if ((*this)(position) != NULL) {
      piece_exists = true;
    }

    // throws exceptions if necessary
    if (!valid_designator) {
      throw Exception("invalid designator");
    }
    if (!valid_position) {
      throw Exception("invalid position");
    }
    if (piece_exists) {
      throw Exception("position is occupied");
    }

    // updates map if an exception is not thrown
    occ[position] = create_piece(piece_designator);

  }

  // prints the board
  void Board::display() const {

    char first_pos = 'A';
    char second_pos = '8';
    int row_num = 8;
    int counter = 7;
    
    // prints beginning of display
    cout << "  ABCDEFGH " << endl;
    cout << "  -------- " << endl;

    for (int i = 0; i < 64; i++) {
      // adds row numbers to left-hand side of board
      if (i % 8 == 0 && row_num > 0) {
        cout << row_num << "|";
      }

      // sets colors of tiles for even rows
      if (row_num % 2 == 0) {
        if (i % 2 == 0) {
          Terminal::color_bg(Terminal::MAGENTA);
	        Terminal::color_fg(true, Terminal::BLACK);
        }
        else {
          Terminal::color_bg(Terminal::BLACK);
	        Terminal::color_fg(true, Terminal::WHITE);
        }
      }

      // sets colors of tiles for odd rows
      else {
        if (i % 2 == 1) {
          Terminal::color_bg(Terminal::MAGENTA);
	         Terminal::color_fg(true, Terminal::BLACK);
        }
        else {
          Terminal::color_bg(Terminal::BLACK);
	        Terminal::color_fg(true, Terminal::WHITE);
        }
      }

      // adds piece to board if piece exists at position
      Position pos = std::make_pair(first_pos, second_pos);
      auto it = occ.find(pos);     
      if (it != occ.end()) {
        Piece * piece = occ.at(pos);
        cout << piece->to_unicode().c_str();
      }
      else {
	      cout << " ";
      }

      // updates position
      if (i == counter && i  > 0) {
        Terminal::set_default();
	      cout << "|" << row_num << endl;
	      row_num--;
        second_pos--;
	      first_pos = 'A';
	      counter+=8;
      }
      else {
        first_pos++;
      }
    }
   
    // prints end of display
    cout << "  -------- " << endl;
    cout << "  ABCDEFGH " << endl;
  }

  std::map<Position, Piece*> Board::get_occ() const {
    return occ;
  }
  
  bool Board::has_valid_kings() const {

    int white_king_count = 0;
    int black_king_count = 0;

    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      if (it->second) {
	      switch (it->second->to_ascii()) {  
	      case 'K':
	        white_king_count++;
	        break;
	      case 'k':
	        black_king_count++;
	        break;
	      }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  void Board::change_pos(const Position& start, const Position& end, Piece * piece, char ascii_char) {
    Piece * captured_piece = occ[end];

    if(captured_piece) {	
        delete captured_piece;
    }

    occ[end] = piece;

    // changes position of piece in the case that a pawn is promoted to a queen
    if (ascii_char == 'p' && end.second == '1') {
      if(piece) {
	      delete piece;
      }
      occ.erase(end);
      add_piece(end, 'q');
    }

    else if (ascii_char == 'P' && end.second == '8') {
      if(piece)	{
        delete piece;
      }
      occ.erase(end);
      add_piece(end, 'Q');
    }
    occ.erase(start);
  }

  // updates the map after a piece is moved
  Piece* Board::change_map(const Position& start, const Position& end, Piece * piece, char ascii_char) {
    // "move" pawn to end position
    occ[end] = piece;
    occ.erase(start);

    // promote pawn to queen
    if (ascii_char == 'p' && end.second == '1') {
      occ.erase(end);
      add_piece(end, 'q');
      return occ[end];
    }
    else if (ascii_char == 'P' && end.second == '8') {
      occ.erase(end);
      add_piece(end, 'Q');
      return occ[end];
    }
    occ.erase(start);
    return occ[end];
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	      const Piece* piece = board(Position(c, r));
	      if (piece) {
	        os << piece->to_ascii();
	      } else {
	        os << '-';
	      }
      }
      os << std::endl;
    }
    return os;
  }
}
