# CPPChess
School Project - Programming Chess in C++

TEAM
rgondek1 RITA GONDEK
jhan62 JOHN HAN
wtong10 WILLIAM TONG

DESIGN
The subclasses of Piece (King.h, Queen.h, Rook.h, Knight.h, Bishop.h, Pawn.h) represent various specific chess pieces. Their completion relied upon overloading Piece's legal_move_shape function and, where applicable, the legal_capture_function. We approached each subclass depending on its individual movement/capture specifications, using if statements to check for a particular piece's legal movements (for instance, checking whether the ratio of the absolute value of the numerator and denominator is equal to one in Bishop.cpp, in order to determine whether a legal diagonal movement was completed) and returning true when fulfilled, false when not.

There are three primary functions in Game.cpp (in_check, in_mate, and in_stalement). In in_check, we first identify the position of the King and, then, determine whether any enemy pieces could legally capture the King. In in_mate, we iterate through every player's pieces and test each move on every possible position on the board. If any of the player's moves are valid, then the player is not in checkmate. In in_stalemate, we iterate through every player's pieces and determine whether they have any valid moves remaining.

Due to its complex private field, which maps a position to a pointer to a Piece object, Board.cpp needed to obey the rule of three. Thus, we implemented the copy constructor as well as the assignment operator and destructor (both of which used the helper function clear()). We, then, overloaded the () operator using a const_iterator and implemented add_piece, is_valid_designator, is_valid_position, piece_promotion, and has_valid_kings. We finished off Board.cpp with our implementation of display(), which we configured to display real chess pieces in the terminal window by mapping the designator char to the corresponding unicode of the chess piece in a std::map. We also made sure to check whether the piece is not found in the map, which would indicate a mystery piece and lead our program to display a letter (M for mystery, for instance).

COMPLETENESS
To our knowledge, our solution is complete and works as indicated in the project document. We are unaware of any missing or incorrect functionality.
