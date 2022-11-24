#ifndef PROGRAM_PARAMS_H_
#define PROGRAM_PARAMS_H_

#include <vector>
#include <string>
#include <iostream>

namespace params {

// Alias ui to unsigned int for convenience
  typedef unsigned int ui;

// Define a struct to hold the paramters section
  struct parameters {
    ui numColors;
    ui boardSize;
    ui numSnails;
  };

// Define a struct to hold the initialization section
  struct snail {
    ui id;
    ui row;
    ui col;
    ui orientation;
  };

// Define a struct to hold the color section
  struct color {
    ui id;
    ui nextColor;
    int deltaOrientation;
  };

// Define struct which holds the parameters coming from the INI file
  struct settings {
    parameters p;
    std::vector<snail> s;
    std::vector<color> c;
  };

// Declare function to return a settings struct from the INI file
  settings read_ini(std::string filename);

}

#endif
