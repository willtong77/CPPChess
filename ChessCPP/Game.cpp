// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <cassert>
#include <cmath>
#include "Game.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {

    // Testing to see if the given positions are on the board
    bool start_valid = (start.first >= 'A') && (start.first <= 'H') && (start.second >= '1') && (start.second <= '8');
    bool end_valid = end.first >= 'A' && end.first <= 'H' && end.second >= '1' && end.second <= '8';
    if (!start_valid) { throw Exception("start position is not on board"); }
    if (!end_valid)   { throw Exception("end position is not on board"); }

    // Testing if there is a piece at the start position
    if (board(start) == nullptr) { throw Exception("no piece at start position"); }

    // Testing if piece color and turn match
    bool white = board(start)->to_ascii() <= 82;
    if (white != is_white_turn) { throw Exception("piece color and turn do not match"); }

    // Testing legality of move shape
    if (board(end) == nullptr) {
      bool legal_move = board(start)->legal_move_shape(start, end);
      if (!legal_move) { throw Exception("illegal move shape"); }
    }

    // Testing legality of capture shape and whether the move captures an opponent
    else {
      bool opponent = white != board(end)->is_white();
      bool legal_capture = board(start)->legal_capture_shape(start, end);

      if (!opponent)      { throw Exception("cannot capture own piece"); }
      if (!legal_capture) { throw Exception("illegal capture shape"); }
    }

    // Checking if the move causes the piece to illegally cross another piece
    if (is_blocked(start, end)) { throw Exception("path is not clear"); }

    // Testing to see if the move causes a check
    if (causes_check(white, start, end)) { throw Exception("move exposes check"); }

    // By this point, the move is valid, so we will carry out the move
    board.remove_piece(end); // If there is no piece, this doesn't change anything
    board.add_piece(end, board(start)->to_ascii());
    board.remove_piece(start);

    board.piece_promotion(is_white_turn);

    is_white_turn = !is_white_turn;
  }

  bool Game::causes_check(bool white, std::pair<char, char> start, std::pair<char, char> end) const {
    Game temp;
    temp.board = this->board;
    temp.is_white_turn = this->is_white_turn;

    temp.board.remove_piece(end);
    temp.board.add_piece(end, temp.board(start)->to_ascii());
    temp.board.remove_piece(start);
    
    return temp.in_check(white);
  }

  bool Game::is_blocked(std::pair<char, char> start, std::pair<char, char> end) const {
    int xd = end.first - start.first;   // x distance
    int yd = end.second - start.second; // y distance
    int xs = 0; // x scale
    int ys = 0; // y scale

    if (xd == 0 && yd == 0) return true;

    // The following booleans check for a move of 1 square, meaning there is no potential of crossing another piece
    bool horizontal = (yd      == 0 && abs(xd) == 1);
    bool vertical   = (xd      == 0 && abs(yd) == 1);
    bool diagonal   = (abs(xd) == 1 && abs(yd) == 1);

    // Crossing does not apply to Knights
    // Don't have to check if the start has a piece because we're the only ones calling this function
    bool knight = board(start)->to_ascii() == 'N' || board(start)->to_ascii() == 'n';

    std::pair<char, char> it_pos;
    // If the piece is not a knight or it doesn't move a single square
    if (!(knight || horizontal || vertical || diagonal)) {
      if (yd == 0) { // Horizontal move
        it_pos.second = start.second;
        xs = xd / abs(xd);
        for (char x = start.first + xs; x != end.first; x += xs) {
          it_pos.first = x;
          if (board(it_pos) != nullptr) return true;
        }
      }
      else if (xd == 0) { // Vertical move
        it_pos.first = start.first;
        ys = yd / abs(yd);
        for (char y = start.second + ys; y != end.second; y += ys) {
          it_pos.second = y;
          if (board(it_pos) != nullptr) return true;
        }
      }
      else { // Diagonal move
        ys = yd / abs(yd);
        xs = xd / abs(xd);
        char x = start.first + xs;
        char y = start.second + ys;
        while (y != end.second && x != end.first) {
          it_pos.first = x;
          it_pos.second = y;
          if (board(it_pos) != nullptr) return true;
          x += xs;
          y += ys; 
        }
      }
    }
    return false;
  }

  bool Game::in_check(bool white) const {
    std::pair<char, char> it_pos;   // Iterating position
    std::pair<char, char> king_pos; // King's position
    char king = white ? 'K' : 'k';  // Setting king character to correct case based on color
    char king_found = false;
    bool capture, opponent;
    
    // Identifying the king's position and storing it in king_pos
    for (int c = 'A'; c <= 'H'; c++) {
      for (int r = '1'; r <= '8'; r++) {
        // Setting king's position as an iterator
        king_pos.first  = c;
        king_pos.second = r;

        // Skip this iteration if there is no piece at the iterated position
        if (board(king_pos) == nullptr) continue;

        // If there is a piece at the iterated position and it's the king, break out of the loop
        if (board(king_pos)->to_ascii() == king) {
          king_found = true;
          break;
        }
      }
      if (king_found) { break; }
    }

    // Checking if any pieces can directly attack the king
    for (int c = 'A'; c <= 'H'; c++) {
      for (int r = '1'; r <= '8'; r++) {
        // Setting iterator it_pos
        it_pos.first  = c;
        it_pos.second = r;

        // Skip this iteration if there is no piece at the iterated position
        if (board(it_pos) == nullptr) continue;

        // Checks if the given piece belongs to the opponent
        opponent = white != board(it_pos)->is_white();
        // Checks if the given piece can capture the king
        capture = board(it_pos)->legal_capture_shape(it_pos, king_pos);

        if (!is_blocked(it_pos, king_pos) && opponent && capture) return true;
      }
    }
    return false;
  }
  
  bool Game::in_mate(bool white) const {
    // The player has to be checked to be in checkmate
    if (!in_check(white)) return false;

    std::pair<char, char> start, end;
    bool valid_end, successful_move;

    for (char c_start = 'A'; c_start <= 'H'; c_start++) {
      for (char r_start = '1'; r_start <= '8'; r_start++) {
        start.first = c_start;
        start.second = r_start;

        // If the piece at the iterated position belongs to the player
        if ((board(start) != nullptr) && (white == board(start)->is_white())) {
          for (char c_end = 'A'; c_end <= 'H'; c_end++) {
            for (char r_end = '1'; r_end <= '8'; r_end++) {
              // Setting iterator for end
              end.first = c_end;
              end.second = r_end;
              valid_end = (board(end) == nullptr) || (white != board(end)->is_white());

              // If the iterated destination position is valid (not a piece of the same color);
              if (valid_end) {
                // Creating new Game object for testing
                Game temp;
                temp.board = this->board;
                temp.is_white_turn = this->is_white_turn;
              
                // Boolean to test for successful move - updated in try/catch block if move unsuccessful
                successful_move = true;

                // Testing the move
                try {
                  temp.make_move(start, end);
                } catch (Exception&) { 
                  successful_move = false;
                }
                // If the move was successful the player is not in checkmate
                if (successful_move) return false;
              }
            }
          }
        }
      }
    }
   
    // If there are no successful moves, then the player is in checkmate
    return true;
  }

  bool Game::in_stalemate(bool white) const {
    // Stalemate requires that the player is not in a checked position
    if (in_check(white)) return false;
    std::pair<char, char> it_pos;   // Iterating position

    for (char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
        // Setting iterator it_pos
        it_pos.first = c;
        it_pos.second = r;

        // Skip this iteration if there is no piece at the iterated position
        if (board(it_pos) == nullptr) continue;

        // If the piece belongs to the opponent, skip this iteration
        if (white != board(it_pos)->is_white()) continue;

        // If the current piece has a valid move, then return false
        if (has_valid_moves(white, it_pos)) return false;
      }
    }
    return true;
  }

  bool Game::has_valid_moves(bool white, std::pair<char, char> start) const {
    std::pair<char, char> it_pos;
    for (char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
        // Setting iterator it_pos
        it_pos.first = c;
        it_pos.second = r;

        // If the piece can't legally move to the iterated position, skip this iteration
        if ((board(it_pos) == nullptr)) {
          if (!board(start)->legal_move_shape(start, it_pos)) continue;
        }
        // Else if the piece can't legally capture at the iterated position, skip this iteration
        else {
          if (!(white != board(it_pos)->is_white() && (board(start)->legal_capture_shape(start, it_pos)))) continue;
        }

        // If the move causes the player to be in a checked position, skip this iteration
        if (causes_check(white, start, it_pos)) continue;

        // If the move is blocked, skip this iteration
        if (is_blocked(start, it_pos)) continue;
        
        // By this point, the move is a legal capture or move, does not put the King in check, and is not blocked, and therefore a valid move
        return true;
      }
    }
    // If there are no valid moves found in the loop, then there are no valid moves at all
    return false;
  }

  void Game::add_piece(std::pair<char, char> position, char piece_designator) {
    board.add_piece(position, piece_designator);
  }

  void Game::clear_board() {
    Board empty_board;
    this->board = empty_board;
  }

  // Reads the board in from a stream
  std::istream& operator>> (std::istream& is, Game& game) {
    // Clearing the current board
    game.clear_board();

    // Reading the board from stream and updating this board
    char input; 
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
        is >> input; 
        if (input == '-') continue;

        std::pair<char, char> position(c, r); 
        game.add_piece(position, input); 
      }
    }
    char turn; 
    is >> turn; 
    bool white = (turn == 'w') ? true : false;
    game.set_turn(white);
    return is; 
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }
}
