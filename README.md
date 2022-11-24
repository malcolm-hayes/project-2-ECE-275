# Project 2: The Great Snail Race!

<center>
	![img](https://static.wikia.nocookie.net/spongebob/images/e/e0/379.png/revision/latest?cb=20130327121057)
</center>	

## Overview: 
In this project we will extend the Langton's Ant to have multiple Ants and multiple Colors. 
This project will build off of work done in Project 1: Have You Seen this Snail.

## Program Overview:
The main idea for Project 2 is the same as Project 1: at each iteration of the algorithm take change the Snail's orientation based on the current Cell in the grid and change the color of that Cell. Now, imagine there are multiple colors each Cell may take where each color changes the orientation differently. Imagine as well there are multiple Snails on the board at any given time. 

That is what we will do herein in Project 2! 

### Specifics:
You will again create (or modify existing) user-defined classes:  

* `Board`: The `Board` comprises a `N` by `N` grid of `Cell` objects and holds `S` number of `Snail` objects which move around the grid
* `Snail`: The `Snail` (formerly known as class `Gary` for Project 1) moves around the `Board` taking one step per iteration
* Cell: The `Cell` comprises the grid on which the `Snail` moves. The `Cell` has `C` possible colors and a mapping `C_current --> C_next` along with a parameter which denotes how the `Snail` will change it's orientation given a particular color.

You will also create a `Program` class to parameterize each of the above classes. 

## Program Parameterization:
Your program will parameterize through a settings file in the INI format. 
The parameterization file will be given as an argument to the executable.
You will provide a method which reads the INI file given as `*(argv + 1)` (assuming `int main(int argc, char** argv)`) and returns a type `params::settings`. 

```c++
params::settings params::read_ini(std::string filename)
```

### Parameterization Details:
The parameters which we need for this program are 

* The size of the board (type: `unsigned int`). Note that we do not require an odd number as in Project 1! 
* The number of possible colors (type: `unsigned int`)
* The number of snails on the board (type: `unsigned int`)

Foe each `Snail` we need the following information:

* An identifier (type: `unsigned int`) which denotes the order by which a `Snail` moves during each iteration
* An initial row index (type: `unsigned int`)
* An initial column index (type: `unsigned int`)
* An initial orientation (type: `unsigned int`) where `{up = 0, right = 1, down = 2, left = 3}`

For each `Cell` color we need the following information:

* An identifier (type: `unsigned int`) which denotes what value we will use to reference this "color"
* The next color ID that a given cell should be when the color is changed (type: `unsigned int`)
* How this color will change the `Snail`'s orientation (type: `int`). `+N` denotes a clockwise rotation `N` times while `-N` denotes a counterclockwise rotation `N` times. `0` denotes no change in orientation. 

#### Example Parameterization File
An example INI file is given in `settings.ini`. The contents are copied below: 

```INI
; Project 2 "The Great Snail Race" will extend Project 1 from a single snail
; on an NxN Board of Cell's that are either one of two colors to a Board 
; where S snails exist on Cell's with C possible colors. 
; 
; Your program will be parameterized through a settings file written in the INI 
; format. This format is commonly used to initialize programs because it groups
; properties into key-value pairs. This file format is commonly used to both 
; read and store configuration parameters. 

[parameters]
; The parameters section stores necessary values for the entire simulation
; such as how many colors are parameterized herein, how large the board size
; should be, and how many snails will be present on this board
numColors = 4
boardSize = 11
numSnails = 2

[snail/0]
; The initialization section initializes one snail on the board. The 
; id field starts at 0 and increments for every additional snail on the board
; The value for orientation is {up = 0, right = 1, down = 2, left = 3}
id = 0
row = 3
col = 4
orientation = 0

[snail/1]
id = 1
row = 5
col = 0
orientation = 1

[color/0]
; The color section describes what the snail should do when encountering this 
; colored cell. The id starts at 0 and increments with each new color
id = 0
nextColor = 1
deltaOrientation = +2

[color/1]
id = 1
nextColor = 2
deltaOrientation = +1

[color/2]
id = 2
nextColor = 3
deltaOrientation = -2

[color/3]
id = 3
nextColor = 0
deltaOrientation = -1
```

### Parameterization Struct:
A struct has been defined which holds structs which represent each field in the settings INI file:

```c++
namespace params {

// Alias ui to unsigned int for convenience
typedef unsigned int ui;

// Define a struct to hold the parameters section
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
	ui o;
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
```

### INI Parser Function:
You are to create a function `params::settings params::read_ini(std::string filename`) which parses the INI file. 
Note that you are free (and encouraged) to utilize an outside library to parse the INI file. 

The Boost C++ library has functionality for INI parsing and there are many other C/C++ libraries which will parse the INI file format, e.g., the GNU Public Library. 
Whatever library you utilize must be able to compile in a Linux environment (specifically Alpine Linux; reach out via Piazza for assistance with this). 

If you wish to utilize anything outside the Boost library (which is preinstalled in the tester) please reach out ASAP so I can install the necessary packages/dependencies for your library. 
You are also of course free to write the parsing script manually but you must be able to parse the file in any categorical order with each entry in each category being in random order. 

Documentation for the Boost property_tree library is found [here](https://www.boost.org/doc/libs/1_77_0/doc/html/property_tree.html) and an example specifically for an INI file is shown [here](https://stackoverflow.com/questions/6175502/how-to-parse-ini-file-with-boost). Note the Boost library can be "installed" via a header-only library. Simply add the correct header files. [This](https://theboostcpplibraries.com/boost.propertytree) tutorial will be helpful. 

## Class Composition:
The following describes the composition of the various classes used herein. 

### Program Class:
The `Program` class has the following requirements:

* Must inherit from `ProgramBase` abstract base class
* Must hold member variable type `Board` named `board`, i.e., `Board Program::board`
* Must be constructible from `params::settings` structure
	* This is actually done for you within the `ProgramBase` class so one may just delegate construction to the base class for the given input parameter 
* Must contain a member function `Program::step()` which executes one iteration of the algorithm.
	* Override this function declared as a pure virtual function within the `ProgramBase` class

#### Explanation:
* You are to construct the `Program` object from the `params::settings` type struct which holds the program settings for the given INI parameterization file. 
	* You should properly initialize the `Board` type member object given the parameterized constructor as given in the abstract base class.
* The tester will call `Program::step()` to test your program. This should represent one single iteration of the algorithm. 

### Board Class:
The `Board` class has the following requirements:

* Must be constructible given a type `params::settings*` parameter. This should completely initialize the `Board` class. 
* Must inherit publicly from `BoardBase`
* Must implement `BoardBase` pure virtual functions to return a cell at a given `(row, col)` in the board and to return the `Snail` type object at index `i`. (See header file for declarations). 


#### Explanation:
* The `Board` should be completely parameterized given a `params::settings*` type argument. This is specifically tested 
* You may freely implement how to store and manipulate each `Cell` and `Snail` type object on the board as the overridden member functions will provide access to each `Cell` and `Snail` when testing. 

### Snail Class:
The following will outline the requirements of `Snail`. 

* Must be constructible given arguments of type `params::snail*` and `const unsigned int` where the 2nd argument is the boardSize.  
* Must inherit from `SnailBase` and override the pure virtual member functions
	* `virtual void step(Cell*) = 0;` should move the snail by one step, i.e., change orientation then move forward and change the color of the `Cell`
	* `virtual orientation get_orientation() = 0;` this should return the current orientation
	* `virtual std::tuple<unsigned int, unsigned int> get_location() = 0;` this should return the location in `(row, col)` order

#### Explanation: 
The `Snail` class mimics closely the `Gary` class from Project 1. There is no change to Gary's movement except that you will change orientation by more than one tick clockwise or counterclockwise. Depending on the `Cell`'s color you will change the orientation either clockwise or counterclockwise `N` times. 

### Cell Class:
The following will outline the requirements of `Cell`. 

* The `Cell` class **shall** inherit from the `CellBase` abstract base class. 
* Must be constructible given an argument of type `std::vector<params::color>*` which fully parameterizes the `Cell` object. Each `Cell` should initialize to the color at index 0. 
*Must override `void nextColor(void)` such that the `Cell` changes from it's current color to the next color (as defined in the `params::color` struct)
* Must override `int get_orientationChange()` such that the given the `deltaOrientation` field within `params::color` is returned for the current color
* Must have a field of type `unsigned int` named `color` (this is already done for you in the abstract base class) which holds the ID of the current color. 


#### Explanation: 
The `Cell` class, like `Snail`, mimics the Cell class from Project 1 closely. 
This `Cell` class will add the complexity that it must be derived from a given abstract base class and that there are now more than two colors. 
Since there are more than two colors (represented by `unsigned int` type ID's) we need some mapping between `c(i)` and `c(i+1)`.
From the `params::color` struct we get each color's "nextColor" and how that color changes the `Snail`'s orientation. 

***Hint***: I added the following to my `Cell` class definition:

```c++
// Store where to find the color settings for this run
std::vector<params::color>* settings_colors;
// Store the pointer to the settings for this current color
params::color* current;
```

so that my `Cell` class within `Cell::nextColor()` can update `Cell::color` as the value of `nextColor` from `this -> current`. Then I reassign `Cell::current` as the index `Cell::color` of `Cell::settings_colors`. 


## Algorithms:
The following will give an algorithmic description of each element of this project. 

### Overall Program Flow:
The flow of your program should be as follows:

---
---

* Read the parameters from the INI file: `params::settings s = params::read_ini(std::string filename)`
* Construct a `Program` type object with the settings as an argument: `Program p(s)`
* Run the `Program` for `steps` number of steps: `p.run(steps)`

---
---
Note that `Program::run()` will not be tested using the tester. `Program::run()` should call `Program::step()` for `steps` times where each `Program::step()` denotes one iteration of the algorithm. This functionality is given in the abstract base class. 

### Program Algorithm
The following denotes what actions to perform within `Program::step()`

---
--- 

`void Program::step(void)`:

* For each snail `S` in order of their ID:
	* `S` <-- The current `Snail` object
	* `(r,c)` <-- The current row and col location of `S`
	* `Cell* c` <-- The `Cell` located at `(r,c)`
	* `S.step(c)` Take one step given the current `Cell`

---
---

### Snail Movement Algorithm:
We will consider `S` number of `Snail` objects on an `N` by `N` grid of `Cell` objects which comprise
a `Board`. 
At each iteration `i` we will perform the following actions:

---
---

`void Snail::step(Cell* c)`

* `S` `<--` The current `Snail` object (i.e., `this`)
* Change `S`'s orientation based on `c`'s current color
* Change `c`'s color to the next color: `c -> nextColor();`
* Advance `S` forward one unit in the new orientation
* Check `S` is still on the board. Wrap around if not. 

---
---
Note here that the algorithm pseudocode *explicitly* says to pass `this` to `Cell::nextOrientation(Snail* s)`. 
This is the first time we've actually needed the `this` pointer.
We want the current `Cell` (denoted as `c` in the algorithm) to act upon **this** current `Snail` object which is executing their `Snail::step(Cell* c)` member function. 
Therefore, we can pass the `this` pointer to `Cell::nextOrientation(Snail* s)` such that the current `Snail`'s orientation is changed based on the current `Cell`. 

### Cell Algorithms:
The `Cell` algorithms will be described herein (see hints in the `Cell` class description section). 
A formal outline will not be given. 


# Project 2 Tester
There will be no output comparison test for this program. 
I will test individually your `Cell`, `Snail`, `Board` and `Program` classes for correct functionality as outlined in the README. 

For the `Cell` class I will initialize with random parameters and test the ability to return the current color and orientation change then transition to the next correct color. 

For the `Snail` class I will initialize with random parameters (individual `Snail` objects will be given ID of 0) and will be tested for correct movement under random `Cell` objects. 

For the testing the `Board` and `Program` classes I will initialize a `Program` type object with random parameters and take multiple steps to ensure correct functionality. `Snail` and `Cell` type objects will be accessed through the `Board` class's member functions. Points will be given for `Board` compiling since you've done work overriding those member functions. 

Parsing the INI file will be tested as well given random, procedurally generated INI files. 

## Verbosity: 
For verbose messages define `SNAIL_TEST_VERBOSE`, `CELL_TEST_VERBOSE`, or `PROGRAM_TEST_VERBOSE` for verbose output from one or all of those tests. 

## Score file:
You will be given `results.ini` as an artifact each test. This file holds your score for this project along with weights for each test. 

# Visualizer: 
A visualization can be created using GNUPlot to generate image frames then ffmeg to create an MP4 file from the individual frames. 

You may utilize the visualizer by defining `MAKE_VISUALIZATION` to `1`. The following is given as an example in Program.hpp

```c++
#define MAKE_VISUALIZATION // This will create an animated GIF
```

Even with the generation of visualization, testing should be accomplished rather quickly. 
However, please do not generate visualizations unless (a) you've already passed the tests and want to see the 
visualization or (b) you need the visualization to debug. 

Note that there will be a `solution` and `underTest` visualization created. The `solution` comes from the tester and represents what is "correct". The `underTest` represents your program's execution. 


# Extra Credit: 
For 0.25 points extra (where 1.0 is a 100%) implement multicolored Langton's Ant in your programming language of choice (does not have to be C++) for an infinite board, i.e., instead of having a fixed board size and wrapping boundary conditions the snails operate on an infinite grid of cells. Also create a visualization tool to produce a video (MP4, GIF, or similar) of the simulation. Provide via email to the instructor NLT 12/14 2359 one zip file containing source code and a 1-2 page PDF writeup explaining the code and the visualization. Note the writeup must include instructions on how to run the program and the visualization. 

* 2/3 of extra credit will be awarded for a functional program. 
* 1/3 of extra credit will be awarded for a functional visualization of the program
