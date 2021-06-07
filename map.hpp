#ifndef _MAP_HPP
#define _MAP_HPP

#include <string>
#include <vector>
#include <iostream>
#include "block.hpp"

class Map{
    public:
    Map(){
        for (int i = 0 ; i < 10 ; i++){
            Block* block = getRandomBlock();
            std::cout<<block->getInfo()<<std::endl;
        }
    }
};


#endif