// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <utility>
#include <cmath>

#include "Pawn.h"

namespace Chess {

  bool Pawn::legal_move_shape(std::pair<char, char> start,
			    std::pair<char, char> end) const {

    // transforming pair's chars to ints + storing them in int variables
    // for easy + convenient comparison
    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;
    
    // captures white pawns' initial vertical movements (choice between one
    // and two forward movements)
    if (start_row == '2' && to_ascii() == 'P') {
      if (start_column - end_column == 0) {
	if ((end_row - start_row == 2) || (end_row - start_row == 1)) {
	  return true;
	}
      }
    }
    // captures white pawns' subsequent vertical movements (one forward movement)
    else if (start_row != '2' && to_ascii() == 'P') {
      if (start_column - end_column == 0 && end_row - start_row == 1) {
	return true;
      }
    }
    // captures black pawns' initial vertical movements (choice between one
    // and two forward movements)
    else if (start_row == '7' && to_ascii() == 'p') {
      if (start_column - end_column == 0) {
	if ((start_row - end_row == 2) || (start_row - end_row == 1)) {
	  return true;
	}
      }
    }
    // captures black pawns' subsequent vertical movements (one forward movement)
    else if (start_row != '7' && to_ascii() == 'p') {
      if (start_column - end_column == 0 && start_row - end_row == 1) {
	return true;
      }
    }
    return false;
  }

  bool Pawn::legal_capture_shape(std::pair<char, char> start,
			       std::pair<char, char> end) const { 

    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;
    
    // when dividing difference between the column movement and the row movement
    // an = difference (= numerator and denominator) captures diagonal movements
    // captures white pawns' one-square diagonal capturing movements
    if (to_ascii() == 'P') {
      if (abs(start_column - end_column) == 1) {
	if (end_row - start_row == 1) {
	  return true;
	}
      }
    }
    // captures black pawns' one-square diagonal capturing movements
    else if(to_ascii() == 'p') {
      if(abs(start_column - end_column) == 1) {
	if(start_row - end_row == 1) {
	  return true;
	}
      }
    }
    return false;
  }
}
