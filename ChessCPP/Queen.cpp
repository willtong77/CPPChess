// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <utility>
#include <cmath>

#include "Queen.h"

namespace Chess {

  bool Queen::legal_move_shape(std::pair<char, char> start,
			     std::pair<char, char> end) const {

    // transforming pair's characters to ints + storing them in int variables
    // for easy + convenient comparison 
    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;
    
    // absolute value of subtracted expressions accounts for both leftward &
    // backward + forward & backward movements
    // captures queen's vertical movements 
    if(abs(start_column - end_column) == 0) {
      if(abs(start_row - end_row) >= 1) {
	return true;
      }
    }
    // captures queen's horizontal movements
    else if(abs(start_row - end_row) == 0) {
      if(abs(start_column - end_column) >= 1) {
	return true;
      }
    }

    int numerator = abs(start_column - end_column);
    int denominator = abs(start_row - end_row);

    // prevents arithmetic or floating point exceptions that could potentially
    // result from dividing by 0 at the end of this function
    if(numerator == 0 || denominator == 0) { 
      return false;
    }
    // when diving difference between the column movement and the row movement,
    // an = difference (= numerator and denominator) captures diagonal movements 
    else if((numerator / denominator) == 1) {
      return true;
    }
    return false;
  }
}
