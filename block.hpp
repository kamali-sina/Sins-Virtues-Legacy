#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <string>
#include <vector>
#include <numeric>
#include "item.hpp"
#include "termcolor.hpp"
#include "enemy.hpp"
#include "console_handler.hpp"

/*
In case of adding a new block, add these to the following locations:
    1- Add the defined ID under here and update number of blocks
    2- Add the block to getRandomBlock function switch case
    3- Add Init Vector for block to map.hpp
*/

#define NUMBER_OF_BLOCKS 7
#define NORMALBLOCK 1 
#define DIGABLEBLOCK 2 
#define HOMEBLOCK 3 
#define SHOPBLOCK 4 
#define BLACKSMITHBLOCK 5 
#define CASTLEBLOCK 6
#define TELEPORTERBLOCK 7

#define RANDOMTAG "random"
#define SPECIALTAG "special"

class Block {
    public:
    Block();
    bool tagsContain(std::string tag);
    int getID() { return ID; }
    std::string getName() { return name; }
    std::string getColor() { return color; }
    void setHasPrompt(bool value) { has_prompt = value; }
    void setHasAdjacentDialog(bool value) { has_adjacent_dialog = value; }
    bool getHasPrompt() { return has_prompt; }
    int getRarity() { return rarity; }
    bool getHasAdjacentDialog() { return has_adjacent_dialog; }
    virtual std::string getInfo() { return "info_base"; }
    virtual std::string getString() { return colored(name, color); }
    virtual std::string getPrompt() { return "prompt_base"; }
    virtual std::string getAdjacentDialog() { return "adjacent_base"; }
    virtual void run_handler(bool ans) {
        _error("A block with no handler was called!");
    }
    virtual std::string save(std::string path) { return std::to_string(ID); }
    virtual void load(std::string path) { return; }

    protected:
    std::string name;
    int ID = 0;
    std::vector<std::string> tags;
    int rarity;
    bool has_prompt;
    bool has_adjacent_dialog;
    std::string color = WHITE;
};

class NormalBlock : public Block {
    public:
    float ITEM_CHANCE = 0.06;
    NormalBlock(bool no_chest=false);

    std::string getInfo();
    bool getContainsItem() { return contains_item; }
    void setContainsItem(bool value) { contains_item = value; }
    std::string getString();
    std::string getPrompt() { return "Open the chest?(y,n)"; }
    std::string getAdjacentDialog() { return "I can see a chest over there on the ground!"; }
    Item* getItemInside(){ return item_inside; }
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);

    protected:
    bool contains_item;
    Item* item_inside;
};

class DigableBlock : public Block {
    public:
    float ITEM_CHANCE = 0.85;
    DigableBlock();

    std::string getInfo() { return "It looks like I can dig here with a shovel!"; }
    bool getContainsItem() { return contains_item; }
    std::string getString() { return name; }
    Item* getItemInside() { return item_inside; }
    void setContainsItem(bool value) { contains_item = value; }
    std::string save(std::string path);
    void load(std::string path);

    protected:
    bool contains_item;
    Item* item_inside;
};

class HomeBlock : public Block {
    public:
    float ITEM_CHANCE = 1;
    float ENEMY_CHANCE = 0.6;
    HomeBlock();

    std::string getInfo() { return "This looks like a place to rest."; }
    bool getContainsItem() { return contains_item; }
    bool getContainsEnemy() { return contains_enemy; }
    Item* getItemInside() { return item_inside; }
    void setContainsEnemy(bool value) { contains_enemy = value; }
    void setContainsItem(bool value) { contains_item = value; }
    std::string getPrompt() { return "Enter the home?(y,n)"; }
    Enemy* getEnemyInside() { return enemy_inside; }
    std::string getAdjacentDialog() { return "I can see a faint light emitting nearby..."; }
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);

    protected:
    bool contains_item;
    bool contains_enemy;
    Item* item_inside;
    Enemy* enemy_inside;
};

class ShopBlock : public Block {
    public:
    ShopBlock();

    void initStock();
    void printStock();

    std::string getInfo() { return "I can spend the coins I found here and sell my extra stuff."; }
    std::string getPrompt() { return "Enter the shop?(y,n)"; }
    std::string getAdjacentDialog() { return "I can see a shop nearby..."; }
    int indexItem(std::string item_name);
    Item* buyItem(int item_index);
    int getItemPrice(int item_index);
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);

    protected:
    std::vector<Item*> stock;
};

class BlacksmithBlock : public Block {
    public:
    BlacksmithBlock();

    std::string getInfo() { return "I can upgrade my weapons and dismantle the extra stuff I found here."; }
    std::string getPrompt() { return "Enter the blacksmith?(y,n)"; }
    std::string getAdjacentDialog() { return "I can hear hitting on an anvil nearby."; }
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);
};

class CastleBlock : public Block {
    public:
    CastleBlock();
    void initEnemies();

    std::string getInfo() { return "A castle in the middle of nowhere?!"; }
    std::string getPrompt() { return "There is no turning back now, get ready, have healing items, and equip your weapons. Do you want to enter the castle?(y,n)"; }
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);

    protected:
    int max_enemy_count = 4;
    int number_of_enemies; 
    std::vector<Enemy*> enemies;
    Boss* boss;
};

class TeleporterBlock : public Block {
    public:
    TeleporterBlock();

    std::string getInfo() { return "Holy shit what is this? It says here that it can teleport me to anywhere I want!"; }
    std::string getPrompt() { return "Enter the teleporter?(y,n)"; }
    std::string getAdjacentDialog() { return "I can hear some starnge futuristic sounds nearby..."; }
    void run_handler(bool ans);
    std::string save(std::string path);
    void load(std::string path);

    protected:
};

Block *getBlock(int block_id);
Block *getRandomBlock();
Block* spawnBlock();

#endif