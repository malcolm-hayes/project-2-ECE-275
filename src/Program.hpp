#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <vector>
#include <iostream>
#include <string>

#include "Board.hpp"
#include "ProgramBase.hpp"
#include "ProgramParams.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace pt = boost::property_tree;

class Program : public ProgramBase{
public:
        
    Program(params::settings temp_ini) : ProgramBase(temp_ini){} // constructible from params::settings structure
    virtual ~Program() = default;

    virtual void step() override {board.move_snail_once();
    } 
};

#endif

namespace params{
   
        settings read_ini(std::string store){
            pt::ptree params;
            pt::ini_parser::read_ini(store, params); 
            
            params::parameters p;
            p.numColors = params.get<unsigned int>("parameters.numColors");
            p.boardSize = params.get<unsigned int>("parameters.boardSize");
            p.numSnails = params.get<unsigned int>("parameters.numSnails");
        
            std::vector<params::snail>s;
            unsigned int snailNum = 0;

            while (true) {
                params::snail thisSnailSettings;
                std::stringstream ss;
                ss << "snail/" << snailNum;
                std::string fieldName = ss.str();
                
                try {
                    thisSnailSettings.id = params.get<unsigned int>(fieldName+ ".id");
                    thisSnailSettings.row = params.get<unsigned int>(fieldName+ ".row");
                    thisSnailSettings.col = params.get<unsigned int>(fieldName+ ".col");
                    thisSnailSettings.orientation = params.get<unsigned int>(fieldName+ ".orientation");
                }
                
                catch (pt::ptree_error& e){
                break;
                }
                
                ++snailNum;
                s.push_back(thisSnailSettings);
            }

            std::vector<params::color> c;
            unsigned int colorNum = 0;

            while(true){
                params::color setColor;
                std::stringstream ss;
                ss << "color/" << colorNum;
                std::string fieldName = ss.str();
                
                try{ 
                    setColor.id = params.get<unsigned int>(fieldName+ ".id");
                    setColor.nextColor = params.get<unsigned int>(fieldName+ ".nextColor");
                    setColor.deltaOrientation = params.get<int>(fieldName+ ".deltaOrientation");
                }
            
                catch (pt::ptree_error& e){
                break;
                }
                
                ++colorNum;
                c.push_back(setColor); 
            } 

            settings temp_ini;
            temp_ini.p = p;
            temp_ini.c = c;
            temp_ini.s = s;
            
            return temp_ini;
        }
    }

