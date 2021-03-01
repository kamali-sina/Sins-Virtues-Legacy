#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <string>
#include <vector>
#include "item.hpp"
#include "console_handler.hpp"

class Block{
    public:
    Block();
    virtual std::string get_info(){return "info_base";}
    virtual std::string get_string(){return "string_base";}
    virtual std::string get_prompt(){return "prompt_base";}
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
    NormalBlock(bool no_chest);
    std::string get_info();
    std::string get_string();
    std::string get_prompt();
    void prompt_handler(int ans);

    bool contains_item;
    Item item_inside;
};

#endif