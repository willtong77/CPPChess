// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <utility>
#include <cmath>

#include "Knight.h"

namespace Chess {

  bool Knight::legal_move_shape(std::pair<char, char> start,
			      std::pair<char, char> end) const {

    // transforming pair's chars to ints + storing them in int variables
    // for easy + convenient comparison
    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;
    
    // captures knight's L-shape when long vertical portion runs horizontally
    if(abs(start_column - end_column) == 2) {
      if(abs(start_row - end_row) == 1) {
	return true;
      }
    }
    // captures knight's L-shape when long vertical portion runs vertically
    else if(abs(start_column - end_column) == 1) {
      if(abs(start_row - end_row) == 2) {
	return true;
      }
    }
    return false;
  }
}
