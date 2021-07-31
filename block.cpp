#include "block.hpp"
#include "console_handler.hpp"
#include <cstdlib>

using namespace std;

/* ==================== Block ==================== */

Block::Block(): tags() {
    name = "block";
    rarity = 1;
    has_prompt = false;
    has_adjacent_dialog = false;
    color = WHITE;
}

bool Block::tagsContain(std::string tag) {
    for (int i = 0 ; i < tags.size() ; i++) {
        if (tags[i] == tag) return true;
    }
    return false;
}

/* ==================== NormalBlock ==================== */

NormalBlock::NormalBlock(bool no_chest) {
    tags.push_back("random");
    tags.push_back("loot");
    tags.push_back("prompt");
    rarity = 1;
    ID = NORMALBLOCK;
    name = "normal";
    color = WHITE;
    if (no_chest) {
        contains_item = false;
    }else{
        contains_item = _random() < ITEM_CHANCE;
    }
    has_prompt = contains_item;
    has_adjacent_dialog = contains_item;
    if (contains_item) {
        item_inside = getRandomItem(0);
    }
}

std::string NormalBlock::getInfo() {
    if (contains_item)
        return "Wow there is a chest here!";
    else
        return "nothing special here.";
}

std::string NormalBlock::getString() {
    std::string me = name;
    if (contains_item)
        me += "*";
    return me;
}

/* ==================== DigableBlock ==================== */

DigableBlock::DigableBlock() {
    tags.push_back("random");
    tags.push_back("loot");
    rarity = 10;
    ID = DIGABLEBLOCK;
    name = "digable";
    contains_item = _random() < ITEM_CHANCE;
    has_prompt = false;
    has_adjacent_dialog = false;
    if (contains_item) {
        item_inside = getRandomItem(0);
    }
    color = MAGENTA;
}

/* ==================== HomeBlock ==================== */

HomeBlock::HomeBlock() {
    tags.push_back("random");
    tags.push_back("special");
    rarity = 80;
    ID = HOMEBLOCK;
    name = "home";
    color = GREEN;
    contains_item = _random() < ITEM_CHANCE;
    contains_enemy = _random() < ENEMY_CHANCE;
    has_prompt = true;
    has_adjacent_dialog = true;
    if (contains_enemy) {
        enemy_inside = getRandomEnemy(0);
    }
    item_inside = getRandomItem(0);
}

/* ==================== ShopBlock ==================== */

ShopBlock::ShopBlock() {
    tags.push_back("random");
    tags.push_back("special");
    rarity = 100;
    ID = SHOPBLOCK;
    name = "shop";
    color = YELLOW;
    has_prompt = true;
    has_adjacent_dialog = true;
    initStock(); 
}

void ShopBlock::initStock() {
    vector<string> ignored_tags({NOTBUYABLETAG});
    for (int i = 0 ; i < ITEMCOUNT ; i++) {
        Item* item = getItem(i);
        if (item->tagsContain(NOTBUYABLETAG)) continue;
        item->rerollPrice();
        stock.push_back(item);
    }
}

int ShopBlock::indexItem(std::string item_name) {
    for (int i = 0 ; i < stock.size() ; i++ ) {
        if (stock[i]->getName() == item_name)
            return i;
    }
    return -1;
}

Item* ShopBlock::buyItem(std::string item_name) {
    int index = indexItem(item_name);
    Item* item = stock[index];
    stock.erase(stock.begin() + index);
    return item;
}

/* ==================== BlacksmithBlock ==================== */

BlacksmithBlock::BlacksmithBlock() {
    tags.push_back("random");
    tags.push_back("special");
    rarity = 120;
    ID = BLACKSMITHBLOCK;
    name = "blacksmith";
    color = BLUE;
    has_prompt = true;
    has_adjacent_dialog = true; 
}

/* ==================== CastleBlock ==================== */

CastleBlock::CastleBlock() {
    number_of_enemies = (int)(_random() * max_enemy_count) + 1;
    rarity = 9999;
    tags.push_back("special");
    ID = CASTLEBLOCK;
    name = "castle";
    color = BOLDCYAN;
    has_prompt = true;
    has_adjacent_dialog = false;
    initEnemies(); 
}

void CastleBlock::initEnemies() {
    for (int i = 0 ; i < number_of_enemies ; i++) {
        enemies.push_back(getRandomEnemy());
    }
    //TODO: spawn boss
    boss = getRandomEnemy();
}

/* ==================== Getters ==================== */

Block *getBlock(int block_id) {
    switch (block_id) {
        case NORMALBLOCK: return new NormalBlock();
        case DIGABLEBLOCK: return new DigableBlock();
        case HOMEBLOCK: return new HomeBlock();
        case SHOPBLOCK: return new ShopBlock();
        case BLACKSMITHBLOCK: return new BlacksmithBlock();
        case CASTLEBLOCK: return new CastleBlock();
        default: return new Block();
    }
}
//TODO: fix random function to account for rarity
Block* getRandomBlock() {
    int block_id = (rand() % NUMBER_OF_BLOCKS) + 1;
    return getBlock(block_id);
}