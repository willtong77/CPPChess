#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::Board(const Board& rhs) {
    std::map<std::pair<char, char>, Piece*>::const_iterator it; 
    for (it = rhs.occ.begin(); it != rhs.occ.end(); it++) {
      if (it->second == nullptr) { occ[it->first] = nullptr; }
      else { add_piece(it->first, (it->second)->to_ascii()); }
    }
  }

  Board::~Board() {
    clear(); 
  }

  void Board::clear() {
    std::map<std::pair<char, char>, Piece*>::const_iterator it; 
    for (it = occ.begin(); it != occ.end(); it++) {
      delete it->second; 
    }
    occ.clear();
  }

  Board& Board::operator=(const Board& rhs) {
    clear(); 
    std::map<std::pair<char, char>, Piece*>::const_iterator it; 
    for (it = rhs.occ.begin(); it != rhs.occ.end(); it++) {
      if (it->second == nullptr) { occ[it->first] = nullptr; }
      else { add_piece(it->first, (it->second)->to_ascii()); }
    }
    return *this;
  }

  const Piece* Board::operator()(std::pair<char, char> position) const {
    std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position); 
    if (it != occ.end()) {
      return it->second; 
    } 

    return nullptr; 
  }

  void Board::remove_piece(std::pair<char, char> position) { 
    if (occ[position] != nullptr) {
      delete occ[position];
      occ[position] = nullptr;
    }
  }

  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    if (!is_valid_position(position)) {
      return false; 
    }

    const Piece *piece = (*this)(position); 
    if (piece != nullptr) {
      // already exists
      return false; 
    }
    // doesn't exist, and valid position
    if (!is_valid_designator(piece_designator)) {
      return false; 
    }
    // good to add now!

    //occ.insert(std::pair<std::pair<char, char>, Piece*>(position, create_piece(piece_designator)));
    occ[position] = create_piece(piece_designator);
    return true; 
  }

  bool Board::is_valid_designator(char des) {
    return des == 'K' || des == 'k' || des == 'Q' || des == 'q' || 
            des == 'B' || des == 'b' || des == 'N' || des == 'n' ||
            des == 'R' || des == 'r' || des == 'R' || des == 'r' ||
            des == 'P' || des == 'p'; 
  }

  bool Board::is_valid_position(std::pair<char, char> position) {
    char row = position.first; 
    char col = position.second; 

    if (row < 'A' && row > 'H') {
      return false; 
    } else if (col < '1' && col > '8') {
      return false; 
    }
    return true; 
  }

  void Board::piece_promotion(bool white) {
    char pawn = white ? 'P' : 'p';
    char row = white ? '8': '1';
    char queen = white ? 'Q' : 'q';
    std::pair<char, char> it_pos;
    it_pos.second = row;

    for (char col = 'A'; col <= 'H'; col++) {
      it_pos.first = col;

      if (occ[it_pos] == nullptr) continue;

      if (occ[it_pos]->to_ascii() == pawn) {
        remove_piece(it_pos);
        add_piece(it_pos, queen);
      }
    }
  }

  bool Board::has_valid_kings() const {
    int num_kingsW = 0;
    int num_kingsB = 0; 
    std::map<std::pair<char, char>, Piece*>::const_iterator it; 
    for (it = occ.begin(); it != occ.end(); it++) {
      if ((it->second)->to_ascii() == 'K') {
        num_kingsW++; 
      } else if ((it->second)->to_ascii() == 'k') {
        num_kingsB++; 
      }
    }
    // MAYBE TODO: if two kings are next to each other

    // valid if there's only 2 kings and they are different color
    return num_kingsW + num_kingsB == 2 && num_kingsW == num_kingsB; 
  }

  void Board::display() const {
    using std::cout; 
    using std::endl; 

    // Terminal::color_fg(true, TERMINAL::WHITE); 
    // Terminal::color_bg(true, TERMINAL::BLACK); 
    std::map<char, std::string> to_chess_unicode = {
        {'K', "\u2654"},
        {'k', "\u265A"},
        {'Q', "\u2655"},
        {'q', "\u265B"},
        {'B', "\u2657"},
        {'b', "\u265D"},
        {'R', "\u2656"},
        {'r', "\u265C"},
        {'N', "\u2658"},
        {'n', "\u265E"},
        {'P', "\u2659"},
        {'p', "\u265F"}
    }; 

    int row_num = 8; 
    for (char r = '8'; r >= '1' ; r--) {
      Terminal::color_fg(true, Terminal::WHITE); 
      cout << row_num << " "; 
      for (char c = 'A'; c <= 'H'; c++) {
        if (((int)r + (int)c) % 2 == 0) {
          Terminal::color_bg(Terminal::BLACK);
        } else {
          Terminal::color_bg(Terminal::WHITE);
        }
        std::pair<char, char> position;
        position = std::make_pair(c, r); 
        const Piece *piece_here = (*this)(position); 
        if (piece_here != nullptr) {
          char piece = tolower(piece_here->to_ascii());
          // check which color it is
          if (piece_here->is_white()) {
            Terminal::color_fg(true, Terminal::MAGENTA); 
          } else {
            Terminal::color_fg(true, Terminal::CYAN); 
          }
          std::map<char, std::string>::const_iterator it = to_chess_unicode.find(piece); 
          if (it == to_chess_unicode.end()) {
            cout << piece << " "; 
          } else {
            cout << to_chess_unicode[piece] << " ";
          }
        } else { 
          Terminal::color_fg(true, Terminal::WHITE); 
          cout << "  "; 
        }
        if (c == 'H') {
          Terminal::color_bg(Terminal::DEFAULT_COLOR);
        }
      }
      Terminal::color_fg(true, Terminal::WHITE); 
      cout << " " << row_num << endl; 
      row_num--; 
    }

    Terminal::color_fg(true, Terminal::WHITE); 
    cout << "   "; 
    for (char i = 'A'; i <= 'H'; i++) {
      cout << i << " "; 
    }
    cout << endl; 

    Terminal::set_default(); 
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
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
