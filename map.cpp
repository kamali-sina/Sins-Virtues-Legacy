#include "map.hpp"
#include "block.hpp"
#include "console_handler.hpp"
#include "utilities.hpp"
#include "termcolor.hpp"
#include <utility>

using namespace std;

int MAPINIT_VECTOR[NUMBER_OF_BLOCKS][4] =
{
    {NORMALBLOCK, 0, 0},
    {DIGABLEBLOCK, 3, 0},
    {HOMEBLOCK, 2, 6},
    {SHOPBLOCK, 2, 8},
    {BLACKSMITHBLOCK, 1, 8},
};

Map::Map() {
    srand((unsigned int)time(NULL));
    initMap();
    spawnSpecialBlocks();
    completeMap();
}

void Map::initMap() {
    for (int i = 0 ; i < MAPSIZE ; i++) {
        vector<Block*> row;
        for (int i = 0 ; i < MAPSIZE ; i++) {
            row.push_back(new Block());
        }
        map.push_back(row);
    }
}

void Map::spawnSpecialBlocks() {
    int vector_lenght = (int)sizeof(MAPINIT_VECTOR)/(int)sizeof(MAPINIT_VECTOR[0]);
    for (int i = 0 ; i < vector_lenght ; i++) {
        spawnOneSpecialBlock(MAPINIT_VECTOR[i]);
    }
}

int* findInitVector(int block_ID){
    int vector_lenght = (int)sizeof(MAPINIT_VECTOR)/(int)sizeof(MAPINIT_VECTOR[0]);
    for (int i = 0 ; i < vector_lenght ; i++) {
        if (MAPINIT_VECTOR[i][BLOCK_ID] == block_ID) 
            return MAPINIT_VECTOR[i];
    }
    _error("Everything is fucked in findInitVector!");
    exit(0);
}

bool Map::isIndexValidForBlock(std::pair<int,int> index, int block_ID){
    pair<int, int> converted_location = indexToLocation(index);
    int* init_vector = findInitVector(block_ID);
    if (abs(converted_location.first) + abs(converted_location.second) < init_vector[BLOCK_SPAWN_DISTANCE]){
        return false;
    }
    return true;
}

void Map::spawnOneSpecialBlock(int init_vector[]) {
    int i = 0; 
    while (i < init_vector[BLOCK_SPAWN_NUMBER]) {
        pair<int, int> random_indexes(rand() % MAPSIZE, rand() % MAPSIZE);
        if (map[random_indexes.first][random_indexes.second]->getID() != 0) continue;
        if (!isIndexValidForBlock(random_indexes, init_vector[BLOCK_ID])) continue;
        map[random_indexes.first][random_indexes.second] = getBlock(init_vector[BLOCK_ID]);
        i++;
    }
}

void Map::completeMap() {
    for (int i = 0 ; i < MAPSIZE ; i++) {
        for (int j = 0 ; j < MAPSIZE ; j++) {
            if (map[i][j]->getID() != 0) continue;
            spawnRandomBlockAtIndex(pair<int,int>(i,j));
        }
    }
}

bool Map::spawnRandomBlockAtIndex(std::pair<int,int> index) {
    Block* block = getRandomBlock();
    while (!block->tagsContain("random") || !isIndexValidForBlock(index, block->getID())) block = getRandomBlock();
    map[index.first][index.second] = block;
    return true;
}

std::pair<int,int> Map::locationToIndex(std::pair<int,int> location) {
    int helper_value = (int)((MAPSIZE - 1) / 2);
    pair<int,int> index(helper_value - location.first, location.second + helper_value);
    return index;
}

std::pair<int,int> Map::indexToLocation(std::pair<int,int> index) {
    int helper_value = (int)((MAPSIZE - 1) / 2);
    pair<int,int> location(helper_value - index.first, index.second - helper_value);
    return location;
}

void Map::printFullMap() {
    int number_of_dashes = MAPSIZE * 4 - 1;
    for (int j = 0 ; j < number_of_dashes ; j++) cout<<"-";
        cout<<endl;
    for (int i = 0 ; i < MAPSIZE ; i++) {
        for (int j = 0 ; j < MAPSIZE ; j++) {
            string temp(1, map[i][j]->getName()[0]);
            cout<<colored(temp, map[i][j]->getColor())<<" | ";
        }
        cout<<endl;
        for (int j = 0 ; j < number_of_dashes ; j++) cout<<"-";
        cout<<endl;
    }
}

void Map::printPartialMap(int vision, std::pair<int,int> location) {
    pair<int,int> indexes = locationToIndex(location);
    int number_of_dashes = 4 * ((vision * 2) + 1) - 1;
    for (int j = 0 ; j < number_of_dashes ; j++) cout<<"-";
        cout<<endl;
    for (int i = indexes.first - vision ; i <= indexes.first + vision ; i++) {
        for (int j = indexes.second - vision ; j <= indexes.second + vision ; j++) {
            if (!isIndexValid(pair<int,int>(i,j))){
                cout<<colored("X", RED)<<" | ";
                continue;
            }
            string temp(1, map[i][j]->getName()[0]);
            cout<<colored(temp, map[i][j]->getColor())<<" | ";
        }
        cout<<endl;
        for (int j = 0 ; j < number_of_dashes ; j++) cout<<"-";
        cout<<endl;
    }
}

bool Map::isLocationValid(std::pair<int,int> location) {
    pair<int,int> indexes = locationToIndex(location);
    return isIndexValid(indexes);
}

bool Map::isIndexValid(std::pair<int,int> indexes) {
    if (indexes.first < MAPSIZE and indexes.second < MAPSIZE and indexes.first >= 0 and indexes.second >= 0)
        return true;
    return false;
}

Block* Map::getBlockAtLocation(std::pair<int,int> location) {
    pair<int,int> indexes = locationToIndex(location);
    return map[indexes.first][indexes.second];
}

void Map::setBlockAtLocation(std::pair<int,int> location, Block* block) {
    pair<int,int> indexes = locationToIndex(location);
    map[indexes.first][indexes.second] = block;
}

void Map::printAdjacentDialogs(std::pair<int,int> location) {
    set<string> dialog_set;
    pair<int,int> indexes = locationToIndex(location);
    for (int i = -1 ; i < 2 ; i++) {
        for (int j = -1 ; j < 2 ; j++) {
            if (i == 0 && j == 0) continue;
            pair<int,int> new_indexes(indexes.first + i, indexes.second + j);
            if (!isIndexValid(new_indexes)) continue;
            Block* block = map[new_indexes.first][new_indexes.second];
            if (!block->getHasAdjacentDialog()) continue;
            string adj_dialog = block->getAdjacentDialog();
            dialog_set.insert(adj_dialog);
        }
    }
    set<string>::iterator itr;
    for (itr = dialog_set.begin(); itr != dialog_set.end(); itr++){
        dialog("You", *itr, YELLOW, 23);
    }
}