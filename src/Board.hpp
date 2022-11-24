
#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>
#include <fstream>

#include "Snail.hpp"
#include "BoardBase.hpp"
#include "ProgramParams.hpp"



class Board : public BoardBase{ 
public:

    Board (params::settings* s): prog_set(s){

        const auto boardSize = prog_set->p.boardSize;
        const auto numSnails = prog_set->p.numSnails;

        for (unsigned int i = 0; i != numSnails; ++i) {

            auto s_params = &(prog_set->s.at(i));
            snails.emplace_back(s_params, boardSize);
        }

        grid.resize(boardSize); 
        for (unsigned int r = 0; r < boardSize; ++r) {
            for (unsigned int c = 0; c < boardSize; ++c) {
                grid.at(r).push_back(&prog_set->c);
            }
        }
    
    }
    std::vector<Snail> snails;
    
    std::vector<params::snail> s_params; 
    Cell* snail_cell(std::tuple<unsigned int, unsigned int> l){
        const auto row = std::get<0>(l);
        const auto col = std::get<1>(l);
        return &(grid.at(row).at(col));
    }
    
    typedef std::vector<Cell> row;
    typedef std::vector<row> Grid;
    Grid grid;

    void move_snail_once(void){ 
        for (auto& s : snails) {
            Cell* c = snail_cell(s.get_location());
            s.move(c);
        }
    }
    
     Cell* get_cell_at(unsigned int row, unsigned int col) override {
        return snail_cell(std::make_tuple(row, col));
    }

     Snail* get_snail_by_id(unsigned int id) override {
        return &snails.at(id);
    }
    params::settings* prog_set = nullptr;

};

#endif
    

