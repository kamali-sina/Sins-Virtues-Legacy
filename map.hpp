#ifndef _MAP_HPP
#define _MAP_HPP

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <stdlib.h>
#include "block.hpp"
#include "utilities.hpp"

#define MAPSIZE 21
#define BLOCK_ID 0
#define BLOCK_SPAWN_NUMBER 1
#define BLOCK_SPAWN_DISTANCE 2

class Map {
  public:
    Map();
    void printFullMap();
    void printPartialMap(int vision, std::pair<int,int> location);
    bool isLocationValid(std::pair<int,int> location);
    bool isIndexValid(std::pair<int,int> indexes);
    Block* getBlockAtLocation(std::pair<int,int> location);
    void setBlockAtLocation(std::pair<int,int> location, Block* block);
    void printAdjacentDialogs(std::pair<int,int> location);

  private:
    std::vector<std::vector<Block *>> map;
    void initMap(); //all map is Block
    void spawnSpecialBlocks(); //Special ones are created
    void spawnOneSpecialBlock(int init_vector[]); //it needs inputs!
    bool spawnRandomBlockAtIndex(std::pair<int,int> index);
    bool isIndexValidForBlock(std::pair<int,int> index, int block_ID);
    void completeMap(); //Complete rest of the map!
    std::pair<int,int> locationToIndex(std::pair<int,int> location);
    std::pair<int,int> indexToLocation(std::pair<int,int> index);
};

/*
    
    def compass(self, tup):
        vector = (self.castle_location[0] - tup[0], self.castle_location[1] - tup[1])
        if (vector[0] == 0 and vector[1] == 0):
            return 'This is the castle block!'
        direction = ''
        if (vector[0] > 0):
            direction += 'north'
        elif (vector[0] < 0):
            direction += 'south'
        if (vector[1] > 0):
            direction += 'east'
        elif (vector[1] < 0):
            direction += 'west'
        return f'The castle is {colored(direction, "cyan")} from here'

    def get_adjacent_blocks(self, tup):
        x = set()
        for i in [-1,0,1]:
            for j in [-1,0,1]:
                l = (tup[0] + i, tup[1] + j)
                if (not self.is_location_valid(l)): continue
                indexes = self.tup_to_index(l)
                if (not(i == 0 and j == 0)): x.add(type(self.map[indexes[0]][indexes[1]]))
        return x
    
    def get_adjacent_dialogs(self, tup):
        x = set()
        for i in [-1,0,1]:
            for j in [-1,0,1]:
                l = (tup[0] + i, tup[1] + j)
                if (not self.is_location_valid(l)): continue
                indexes = self.tup_to_index(l)
                block = self.map[indexes[0]][indexes[1]]
                if (not block.has_adjacent_dialog): continue
                if (not(i == 0 and j == 0)): x.add(self.map[indexes[0]][indexes[1]].get_adjacent_dialog())
        return x
*/

#endif