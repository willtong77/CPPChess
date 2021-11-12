// rgondek1 RITA GONDEK
// jhan62 JOHN HAN
// wtong10 WILLIAM TONG

#include <utility>
#include <cmath>

#include "Bishop.h"

namespace Chess {

  bool Bishop::legal_move_shape(std::pair<char, char> start,
			      std::pair<char, char> end) const {

    // transforming pair's chars to ints + storing them in int variables
    // for easy + convenient comparison
    int start_column = std::get<0>(start) + 0;
    int start_row = std::get<1>(start) + 0;
    int end_column = std::get<0>(end) + 0;
    int end_row = std::get<1>(end) + 0;

    int numerator = abs(start_column - end_column);
    int denominator = abs(start_row - end_row);
    
    // if there is no movement in the numerator/denominator the player either 
    // placed the Bishop at the same spot (illegal) or did not move the Bishop
    // diagonally (illegal)
    // prevents arithmetic exception that results from dividing by 0 further
    // down in this function
    if(numerator == 0 || denominator == 0) { 
      return false;
    }
    
    // when dividing difference between the column movement and the row movement
    // an = difference (= numerator and denominator) captures diagonal movements
    if((numerator / denominator) == 1) {
      return true;
    }
    return false;
  }
}
