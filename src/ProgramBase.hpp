#ifndef PROGRAM_BASE_H_
#define PROGRAM_BASE_H_

#include "ProgramParams.hpp"

#include "Board.hpp"

class ProgramBase {
public:
  ProgramBase() = delete;
  ProgramBase(params::settings s) : program_params(s), board(&program_params) {}
  virtual ~ProgramBase() = default;

  // Hold the settings
  params::settings program_params;
  Board board;

  // Method to move all snails around the Board for some number of steps
  void run(unsigned int numSteps) {
    for (unsigned int i = 0; i != numSteps; ++i){
      step();
    }
  }
  // Method to take one single step of the program
  virtual void step() = 0;
  
};

#endif
