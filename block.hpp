#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <string>
#include <vector>
#include "item.hpp"
#include "console_handler.hpp"

//TODO: add more blocks

class Block{
    public:
    Block();
    virtual std::string getInfo(){return "info_base";}
    virtual std::string getString(){return "string_base";}
    virtual std::string getPrompt(){return "prompt_base";}
    virtual std::string getAdjacentDialog(){return "adjacent_base";}
    virtual void prompt_handler(int ans){}

    std::string name;
    std::vector<std::string> tags;
    float rarity;
    bool has_prompt;
    bool has_adjacent_dialog;
};

class NormalBlock : public Block{
    public:
    float ITEM_CHANCE = 0.04;
    NormalBlock(bool no_chest=false);
    void prompt_handler(int ans);

    std::string getInfo();
    bool getContainsItem(){return contains_item;}
    std::string getString();
    std::string getPrompt(){return "Open the chest?(y,n)";}
    std::string getAdjacentDialog(){return "I can see a chest over there on the ground!";}

    protected:
    bool contains_item;
    Item item_inside;
};

//TODO: Complete
Block getRandomBlock();

#endif