#include "map.hpp"
#include "block.hpp"
#include "console_handler.hpp"
#include "utilities.hpp"
#include <utility>

using namespace std;

int MAPINIT_VECTOR[NUMBER_OF_BLOCKS][4] =
{
    {NORMALBLOCK, 0, 0 ,0},
    {DIGABLEBLOCK, 3, 0, 0},
    {HOMEBLOCK, 2, 3, 3},
    {SHOPBLOCK, 2, 4, 4},
    {BLACKSMITHBLOCK, 1, 4, 4},
};

Map::Map(){
    srand((unsigned int)time(NULL));
    initMap();
    spawnSpecialBlocks();
    completeMap();
}

void Map::initMap(){
    for (int i = 0 ; i < MAPSIZE ; i++){
        vector<Block*> row;
        for (int i = 0 ; i < MAPSIZE ; i++){
            row.push_back(new Block());
        }
        map.push_back(row);
    }
}

void Map::spawnSpecialBlocks(){
    int vector_lenght = (int)sizeof(MAPINIT_VECTOR)/(int)sizeof(MAPINIT_VECTOR[0]);
    cout<<"spawning special blocks... lenght: "<< vector_lenght<<endl;
    for (int i = 0 ; i < vector_lenght ; i++){
        spawnOneSpecialBlock(MAPINIT_VECTOR[i]);
    }
}

void Map::spawnOneSpecialBlock(int init_vector[]){
    int i = 0; 
    while (i < init_vector[BLOCK_SPAWN_NUMBER]){
        pair<int, int> random_indexes(rand() % MAPSIZE, rand() % MAPSIZE);
        if (map[random_indexes.first][random_indexes.second]->name == "normal") continue;
        pair<int, int> converted_location = indexToLocation(random_indexes);
        if (abs(converted_location.first) < init_vector[BLOCK_SPAWN_ROW] || abs(converted_location.second) < init_vector[BLOCK_SPAWN_COLUMN]) continue;
        map[random_indexes.first][random_indexes.second] = getBlock(init_vector[BLOCK_ID]);
        i++;
    }
}

void Map::completeMap(){
    for (int i = 0 ; i < MAPSIZE ; i++){
        for (int j = 0 ; j < MAPSIZE ; j++){
            if (map[i][j]->name == "normal") continue;
            spawnRandomBlockAtIndex(pair<int,int>(i,j));
        }
    }
}

void Map::spawnRandomBlockAtIndex(std::pair<int,int> index){
    Block* block = getRandomBlock();
    while (!block->tagsContain("random")) block = getRandomBlock();
    map[index.first][index.second] = block;
}

std::pair<int,int> Map::locationToIndex(std::pair<int,int> location){
    int helper_value = (int)((MAPSIZE - 1) / 2);
    pair<int,int> index(helper_value - location.first, location.second + helper_value);
    return index;
}

std::pair<int,int> Map::indexToLocation(std::pair<int,int> index){
    int helper_value = (int)((MAPSIZE - 1) / 2);
    pair<int,int> location(helper_value - index.first, index.second - helper_value);
    return location;
}