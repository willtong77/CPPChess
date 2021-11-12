// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <utility>
#include <cmath>

#include "King.h"

namespace Chess {

  bool King::legal_move_shape(std::pair<char, char> start,
			    std::pair<char, char> end) const {

    // transforming pair's characters to ints + storing them in int variables
    // for easy + convenient comparison
    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;

    // completing the absolute value of subtracted expression accounts for
    // both leftward and rightward moves or forward and backyard moves
    if(abs(start_column - end_column) == 1) {
      if((abs(start_row - end_row) == 1) || (start_row - end_row == 0)) {
	return true;
      }
    }
    // if king only moves vertically, there cannot be no difference between
    // start_row - end_row, as this would indicate remaining in the same
    // space (an illegal move)
    else if(start_column - end_column == 0) {
      if(abs(start_row - end_row) == 1) {
	return true;
      }
      return false;
    }
    return false;
  }
}
