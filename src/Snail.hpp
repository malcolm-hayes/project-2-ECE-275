#ifndef SNAIL_H_
#define SNAIL_H_

#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

#include "Cell.hpp"
#include "SnailBase.hpp"
#include "ProgramParams.hpp"


 inline orientation& operator++(orientation& orient, int) {
    const int i = static_cast<int> (orient) + 1;
    orient = static_cast<orientation> (i % 4);
    return orient;

}

 inline orientation& operator--(orientation& orient, int) {
    const int i = static_cast<int> (orient) - 1;
    if(i<0){
        orient = orientation::left;
    }
    else {
        orient = static_cast<orientation> (i % 4);
    }
    return orient;

}

class Snail : public SnailBase{ 
public:
    unsigned int boardSize;
    
    Snail(params::snail* s, const unsigned int N): boardSize(N){
        orient = static_cast<orientation>(s->orientation);
        coord = std::make_tuple(s->row, s->col);
        x_coordinate = s->col;
        y_coordinate = s->row;
    }
    ~Snail() = default;

    void move(Cell* c) override{

        auto delOrientation = c->get_orientationChange();
        
        while(delOrientation != 0 ){
            if (delOrientation < 0) {
                orient--;
                ++delOrientation;
            }
            else {
                orient++;
                --delOrientation;
            }
        }
        c->nextColor();
        changeOrientation();
    }

     orientation get_orientation() override {
         return orient;
    }

     std::tuple<unsigned int, unsigned int> get_location(void) override {
         return coord;
     }

    std::tuple<unsigned int, unsigned int> coord;

    unsigned int x_coordinate, y_coordinate;

    void changeOrientation(){
        switch (orient) {
                
        case orientation::up:
            --std::get<0>(coord);
        break;

        case orientation::right:
            ++std::get<1>(coord);
        break;
                
        case orientation::down:
            ++std::get<0>(coord);
        break;
                
        case orientation::left:
            --std::get<1>(coord);
        break;

        }
        boardWrap(std::get<0>(coord));
        boardWrap(std::get<1>(coord));
        
        return;
    }

    orientation orient;

    void boardWrap(unsigned int &i){

        if (i == static_cast<unsigned int> (-1) ) {
            i = boardSize - 1;
        }
        else if(i==boardSize){
            i = 0;
        }
    }
private:
};

#endif



