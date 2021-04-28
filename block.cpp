#include "block.hpp"
#include "console_handler.hpp"
#include <cstdlib>

using namespace std;

Block::Block(): tags(){
    name = "";
    rarity = 1;
    has_prompt = false;
    has_adjacent_dialog = false;
    color = WHITE;
}


NormalBlock::NormalBlock(bool no_chest){
    tags.push_back("random");
    tags.push_back("loot");
    tags.push_back("prompt");
    rarity = 1;
    name = "normal";
    color = WHITE;
    if (no_chest){
        contains_item = false;
    }else{
        contains_item = _random() < ITEM_CHANCE;
    }
    has_prompt = contains_item;
    has_adjacent_dialog = contains_item;
    if (contains_item){
        item_inside = getRandomItem(0);
    }
}

std::string NormalBlock::getInfo(){
    if (contains_item)
        return "Wow there is a chest here!";
    else
        return "nothing special here.";
}

std::string NormalBlock::getString(){
    std::string me = name;
    if (contains_item)
        me += "*";
    return me;
}

void NormalBlock::prompt_handler(int ans){
    //TODO
    return;
}


DigableBlock::DigableBlock(){
    tags.push_back("random");
    tags.push_back("loot");
    rarity = 10;
    name = "digable";
    contains_item = _random() < ITEM_CHANCE;
    has_prompt = false;
    has_adjacent_dialog = false;
    if (contains_item){
        item_inside = getRandomItem(0);
    }
    color = RED;
}


HomeBlock::HomeBlock(){
    tags.push_back("random");
    tags.push_back("special");
    rarity = 80;
    name = "home";
    color = GREEN;
    contains_item = _random() < ITEM_CHANCE;
    contains_enemy = _random() < ENEMY_CHANCE;
    has_prompt = true;
    has_adjacent_dialog = true;
    if (contains_enemy){
        enemy_inside = getRandomEnemy(0);
    }
    item_inside = getRandomItem(0);
}

void HomeBlock::prompt_handler(int ans){
    //TODO: complete this after figuring out how to pass game
}


ShopBlock::ShopBlock(){
    tags.push_back("random");
    tags.push_back("special");
    rarity = 100;
    name = "shop";
    color = YELLOW;
    has_prompt = true;
    has_adjacent_dialog = true;
    init_stock(); 
}


BlacksmithBlock::BlacksmithBlock(){
    tags.push_back("random");
    tags.push_back("special");
    rarity = 120;
    name = "blacksmith";
    color = BLACK;
    has_prompt = true;
    has_adjacent_dialog = true; 
}




Block getRandomBlock(){
    int block_id = (rand() % NUMBER_OF_BLOCKS) + 1;
    switch (block_id) {
        case 1: return NormalBlock();
        case 2: return DigableBlock();
        case 3: return HomeBlock();
        case 4: return ShopBlock();
        case 5: ;
        case 6: ;
    }
    return Block();
}