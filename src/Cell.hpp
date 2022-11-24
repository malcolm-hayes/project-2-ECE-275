
#ifndef CELL_H_
#define CELL_H_

#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>
#include <fstream>

#include "ProgramParams.hpp"
#include "CellBase.hpp"


class Cell : public CellBase {
public:
    
    Cell(std::vector<params::color>* params){
        settings_colors = params;
        current = &settings_colors->at(0);
    }
    
    ~Cell() = default;
    
    virtual void nextColor(void) override{
        color = current->nextColor;
        current = &settings_colors->at(color);
    }
    
    virtual int get_orientationChange() override{
        return current->deltaOrientation;
    }
    
    std::vector<params::color>* settings_colors;
    
    params::color* current;
    
    params::color get_color(){
        return *current;
    }
    void next_color();
    
    std::string current_color();
    
private:
    
};

#endif

