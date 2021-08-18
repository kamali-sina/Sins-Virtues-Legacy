#include "block.hpp"
#include "console_handler.hpp"
#include "VnS.hpp"
#include <cstdlib>

using namespace std;

bool is_tensor_valid = false;
vector<float> blocks_tensor;

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
    tags.push_back(RANDOMTAG);
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

void NormalBlock::run_handler(bool ans) {
    if (ans == false) {
        noNormalblockPromptDialog();
        return;
    }
    this->setContainsItem(false);
    this->setHasPrompt(false);
    this->setHasAdjacentDialog(false);
    session.getPlayer()->addItem(this->getItemInside());
    yesNormalblockPromptDialog();
}

/* ==================== DigableBlock ==================== */

DigableBlock::DigableBlock() {
    tags.push_back(RANDOMTAG);
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
    tags.push_back(RANDOMTAG);
    tags.push_back(SPECIALTAG);
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

void HomeBlock::run_handler(bool ans) {
    if (ans == false) {
        noHomeBlockPromptDialog();
        return;
    }
    if (this->getContainsEnemy()) {
        Enemy* enemy = this->getEnemyInside();
        haveToFightEnemyInHomeDialog(enemy->getName());
        session.fightEnemy(enemy);
        this->setContainsEnemy(false);
        restAfterFightDialog();
    }
    cout<<"resting..."<<endl;
    sleep(2);
    session.getPlayer()->refillHP();
    notification("Health fully restored!");
    notification("It's morning now, Game Saved!");
    session.resetWorldTimer();
    if (this->getContainsItem()) {
        this->setContainsItem(false);
        Item* item = this->getItemInside();
        session.getPlayer()->addItem(item);
    }
    // TODO: save game
}

/* ==================== ShopBlock ==================== */

ShopBlock::ShopBlock() {
    tags.push_back(RANDOMTAG);
    tags.push_back(SPECIALTAG);
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
        Item* item = getItem(i + 1);
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

Item* ShopBlock::buyItem(int item_index) {
    Item* item = stock[item_index];
    stock.erase(stock.begin() + item_index);
    return item;
}

int ShopBlock::getItemPrice(int item_index) {
    Item* item = stock[item_index];
    return item->getSellPrice();
}

void ShopBlock::printStock() {
    cout<<"==========Shop Stock==========" << endl;
    cout<<"  name                price" << endl;
    cout<<"------------------------------" << endl;
    for (auto item : stock) {
        cout<< item->getString();
        int spaces = 24 - item->getName().length();
        for (int i = 0 ; i < spaces ; i++) cout<<" ";
        cout<<colored(to_string(item->getSellPrice()),YELLOW) <<endl;
    }
}

void ShopBlock::run_handler(bool ans) {
    if (ans == false) {
        noShopBlockPromptDialog();
    } else {
        session.enterShop();
    }
}

/* ==================== BlacksmithBlock ==================== */

BlacksmithBlock::BlacksmithBlock() {
    tags.push_back(RANDOMTAG);
    tags.push_back(SPECIALTAG);
    rarity = 120;
    ID = BLACKSMITHBLOCK;
    name = "blacksmith";
    color = BLUE;
    has_prompt = true;
    has_adjacent_dialog = true; 
}

void BlacksmithBlock::run_handler(bool ans) {
    if (ans == false) {
        noBlackSmithBlockDialog();
    } else {
        session.enterBlacksmith();
    }
}

/* ==================== CastleBlock ==================== */

CastleBlock::CastleBlock() {
    number_of_enemies = (int)(_random() * max_enemy_count) + 1;
    rarity = 9999;
    tags.push_back(SPECIALTAG);
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

void CastleBlock::run_handler(bool ans) {
    //TODO: complete castle
}

/* ==================== Getters ==================== */

void setBlocksTensor() {
    vector<float> rarities;
    for (int i = 0 ; i < NUMBER_OF_BLOCKS ; i++) {
        Block* block = getBlock(i + 1);
        if (block->tagsContain(RANDOMTAG)) {
            rarities.push_back(1.0 / (float)block->getRarity());
        } else {
            rarities.push_back(0.0);
        }
    }
    float sum_of_rarities = 0;
    for (auto& rarity : rarities) {
        sum_of_rarities += rarity;
    }
    for (int i = 0 ; i < rarities.size() ; i++) {
        rarities[i] = rarities[i] / sum_of_rarities;
    }
    blocks_tensor = rarities;
    is_tensor_valid = true;
}

Block* getBlock(int block_id) {
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

Block* spawnBlock() {
    if (!is_tensor_valid || blocks_tensor.size() == 0) {
        setBlocksTensor();
    }
    float block_chooser = _random();
    for (int i = 0 ; i < blocks_tensor.size() ; i++) {
        if (block_chooser < blocks_tensor[i]) {
            return getBlock(i + 1);
        }
        block_chooser -= blocks_tensor[i];
    }
    _error("this should not happen: spawnBlock!!!");
    exit(0);
}