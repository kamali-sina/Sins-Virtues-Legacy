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
    Map(std::pair<int,int> player_location);
    Map(int seed);
    Map(std::string save_path);
    void printFullMap();
    void printPartialMap(int vision, std::pair<int,int> location);
    bool isLocationValid(std::pair<int,int> location);
    bool isIndexValid(std::pair<int,int> indexes);
    Block* getBlockAtLocation(std::pair<int,int> location);
    void setBlockAtLocation(std::pair<int,int> location, Block* block);
    void printAdjacentDialogs(std::pair<int,int> location);
    std::string compass(std::pair<int,int> location);
    void save(std::string path);
    void load(std::string path);

  private:
    std::vector<std::vector<Block *> > map;
    void initMap(); //all map is Block
    void spawnSpecialBlocks(); //Special ones are created
    void spawnOneSpecialBlock(int init_vector[]); //it needs inputs!
    bool spawnRandomBlockAtIndex(std::pair<int,int> index);
    bool isIndexValidForBlock(std::pair<int,int> index, int block_ID);
    void spawnHomeAtPlayerLocation(std::pair<int,int> player_location);
    void completeMap(); //Complete rest of the map!
    std::pair<int,int> locationToIndex(std::pair<int,int> location);
    std::pair<int,int> indexToLocation(std::pair<int,int> index);
    std::pair<int,int> castle_location_index;
};

#endif