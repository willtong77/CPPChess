#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
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

    // Returns a constant reference to the board
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    const Board& get_board() const { return board; }

    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }

    // Attempts to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(std::pair<char, char> start, std::pair<char, char> end);

    // Helper function to see if a given move will result in a checked position
    // Returns true if it causes a check and false if it doesn't
    bool causes_check(bool white, std::pair<char, char> start, std::pair<char, char> end) const;

    // Helper function to see if a given move's path is blocked
    // Returns true if it is blocked and false if it isn't
    bool is_blocked(std::pair<char, char> start, std::pair<char, char> end) const;

    // Returns true if the designated player is in check
    bool in_check(bool white) const;

    // Returns true if the designated player is in mate
    bool in_mate(bool white) const;

    // Returns true if the designated player is in mate
    bool in_stalemate(bool white) const;

    // Returns true if the designated player has any valid moves remaining
    bool has_valid_moves(bool white, std::pair<char, char> start) const;

    // Helper function to add piece within Game class for istream operator overload
    void add_piece(std::pair<char, char> position, char piece_designator);

    // Helper Function to set the turn
    void set_turn(bool white) {is_white_turn = white; }; 

    // Helper function to clear the board within Game class for istream operator overload
    void clear_board();
  
  private:
    // The board
    Board board;

    // Is it white's turn?
    bool is_white_turn;

  };

  // Reads the board in from a stream
  std::istream& operator>> (std::istream& is, Game& game);
  
  // Writes the board out to a stream
  std::ostream& operator<< (std::ostream& os, const Game& game);


}
#endif // GAME_H
