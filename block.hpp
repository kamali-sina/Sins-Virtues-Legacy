#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <string>
#include <vector>
#include "item.hpp"
#include "termcolor.hpp"
#include "enemy.hpp"
#include "console_handler.hpp"

/*
In case of adding a new block, add these to the following locations:
    1- Add the defined ID under here and update number of blocks
    2- Add the block to getRandomBlock function switch case
    3- Add Init Vector for block to map.hpp
    4- If needed add handler for block at handlers.hpp
*/

#define NUMBER_OF_BLOCKS 5
#define NORMALBLOCK 1 
#define DIGABLEBLOCK 2 
#define HOMEBLOCK 3 
#define SHOPBLOCK 4 
#define BLACKSMITHBLOCK 5 

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
    bool getHasAdjacentDialog() { return has_adjacent_dialog; }
    virtual std::string getInfo() { return "info_base"; }
    virtual std::string getString() { return colored(name, color); }
    virtual std::string getPrompt() { return "prompt_base"; }
    virtual std::string getAdjacentDialog() { return "adjacent_base"; }

    protected:
    std::string name;
    int ID = 0;
    std::vector<std::string> tags;
    float rarity;
    bool has_prompt;
    bool has_adjacent_dialog;
    std::string color = WHITE;
};

class NormalBlock : public Block {
    public:
    float ITEM_CHANCE = 1;
    NormalBlock(bool no_chest=false);

    std::string getInfo();
    bool getContainsItem() { return contains_item; }
    void setContainsItem(bool value) { contains_item = value; }
    std::string getString();
    std::string getPrompt() { return "Open the chest?(y,n)"; }
    std::string getAdjacentDialog() { return "I can see a chest over there on the ground!"; }
    Item* getItemInside(){ return item_inside; }

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
    std::string getPrompt() { return "Enter the home?(y,n)"; }
    std::string getAdjacentDialog() { return "I can see a faint light emitting nearby..."; }

    protected:
    bool contains_item;
    bool contains_enemy;
    Item* item_inside;
    Enemy* enemy_inside;
};

class ShopBlock : public Block {
    public:
    ShopBlock();

    int buyItem(int index);
    int indexItem(std::string item_name);
    void init_stock();

    std::string getInfo() { return "I can spend the coins I found here and sell my extra stuff."; }
    std::string getPrompt() { return "Enter the shop?(y,n)"; }
    std::string getAdjacentDialog() { return "I can see a shop nearby..."; }

    protected:
    std::vector<Item> Stock;
};

class BlacksmithBlock : public Block {
    public:
    BlacksmithBlock();

    //TODO: complete Logic

    std::string getInfo() { return "I can upgrade my weapons and dismantle the extra stuff I found here."; }
    std::string getPrompt() { return "Enter the blacksmith?(y,n)"; }
    std::string getAdjacentDialog() { return "I can hear hitting on an anvil nearby."; }
};

Block *getBlock(int block_id);
Block *getRandomBlock();

#endif