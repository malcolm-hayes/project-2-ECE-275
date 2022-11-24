#ifndef SNAIL_BASE_H_
#define SNAIL_BASE_H_

#include <tuple>
#include <iostream>

#include "Cell.hpp"

enum class orientation {up, right, down, left};

class SnailBase {
public:
  SnailBase() = default;
  virtual ~SnailBase() = default;

  virtual void move(Cell*) = 0;
  virtual orientation get_orientation() = 0;
  virtual std::tuple<unsigned int, unsigned int> get_location() = 0;
};

#endif
