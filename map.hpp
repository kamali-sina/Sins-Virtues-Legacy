#ifndef _MAP_HPP
#define _MAP_HPP

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <stdlib.h>
#include "block.hpp"
#include "utilities.hpp"

#define MAPSIZE 21
#define BLOCK_ID 0
#define BLOCK_SPAWN_NUMBER 1
#define BLOCK_SPAWN_ROW 2
#define BLOCK_SPAWN_COLUMN 3

class Map{
  public:
    Map();
    void printFullMap();
    void printPartialMap(int vision);
    bool isLocationValid(std::pair<int,int> location);
    Block getBlockAtLocation(std::pair<int,int> location);
    void setBlockAtLocation(std::pair<int,int> location, Block block);

  private:
    std::vector<std::vector<Block *>> map;
    void initMap(); //all map is Block
    void spawnSpecialBlocks(); //Special ones are created
    void spawnOneSpecialBlock(int init_vector[]); //it needs inputs!
    void spawnRandomBlockAtIndex(std::pair<int,int> index);
    void completeMap(); //Complete rest of the map!
    std::pair<int,int> locationToIndex(std::pair<int,int> location);
    std::pair<int,int> indexToLocation(std::pair<int,int> index);
};

/*
TODO:
DEFAULT_VALUES = [(DigableBlock, MAP_SIZE//3, (0,0)),
                    (HomeBlock, MAP_SIZE//6, (MAP_SIZE//5, MAP_SIZE//5)),
                    (CastleBlock, 1, (MAP_SIZE//2.5, MAP_SIZE//2.5)),
                    (ShopBlock, MAP_SIZE//7, (MAP_SIZE//4,MAP_SIZE//4)),
                    (BlacksmithBlock, MAP_SIZE//7, (MAP_SIZE//7,MAP_SIZE//4))]

    def print_full_map(self, tup):
        indexes = self.tup_to_index(tup)
        for i in range(MAP_SIZE):
            for j in range(MAP_SIZE):
                if (indexes[0] == i and indexes[1] == j):
                    print(colored(self.map[i][j], 'cyan'), end = "  ")
                    continue
                print(self.map[i][j], end = "  ")
            print()
    
    def print_partial_map(self, tup, vision):
        indexes = self.tup_to_index(tup)
        tool = (vision * 2) + 1
        count = ((tool+1) * 2) + tool + 2
        print(count * '-')
        for i in range(indexes[0] - vision, indexes[0] + vision + 1):
            print('|', end = "  ")
            for j in range(indexes[1] - vision, indexes[1] + vision + 1):
                if (self.is_location_valid(self.index_to_tup([i,j]))):
                    if (indexes[0] == i and indexes[1] == j):
                        print(colored(self.map[i][j].name[0], 'cyan'), end = "  ")
                        continue
                    print(self.map[i][j].get_oneworder(), end = "  ")
                else:
                    print('x', end = "  ")
            print('|')
        print(count * '-')
    
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