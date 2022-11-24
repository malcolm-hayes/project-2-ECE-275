#include "Program.hpp"

#include <string>
#include <cstdlib>

// Call progarm as ./localRun filename numSteps
int main(int argc, char** argv) {
    // Check command arguments
    if (argc != 3) {
        std::cerr << "Call as ./localRun filename numSteps" << std::endl;
        return -1;
    }

    // Read the INI file given in the argument
    std::string filename = *(argv + 1);
    params::settings s = params::read_ini(filename);

    // Construct a Program given the settings
    Program prog(s);
    // Run for some number of steps given in the second argument
    prog.run(std::atoi(*(argv+2)));

    return 0;
}
