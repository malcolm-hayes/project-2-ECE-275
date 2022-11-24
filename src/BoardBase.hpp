#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include "Cell.hpp"
#include "Snail.hpp"

class BoardBase {
public:
  BoardBase() = default;
  virtual ~BoardBase() = default;

  // Method to return a pointer to the Cell type object at (row, col)
  virtual Cell* get_cell_at(unsigned int, unsigned int) = 0;
  // Method to return a pointer to the Snail type with a given ID
  virtual Snail* get_snail_by_id(unsigned int) = 0;

};

#endif
