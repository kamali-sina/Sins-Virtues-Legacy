#include "block.hpp"

using namespace std;

Block::Block(): tags(){
    name = "";
    rarity = 1;
    has_prompt = false;
    has_adjacent_dialog = false;
}


NormalBlock::NormalBlock(bool no_chest){
    tags.push_back("random");
    tags.push_back("loot");
    rarity = 1;
    name = "normal";
    if (no_chest){
        contains_item = false;
    }else{
        contains_item = _random() < ITEM_CHANCE;
    }
    has_prompt = contains_item;
    has_adjacent_dialog = contains_item;
    if (contains_item){
        item_inside = get_random_item(0);
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
    return;
}
