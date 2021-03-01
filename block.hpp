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
    virtual std::string get_adjacent_dialog(){return "adjacent_base";}
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
    void prompt_handler(int ans);

    std::string get_info(){
        if (contains_item)
            return "Wow there is a chest here!";
        else
            return "nothing special here.";
    }
    std::string get_string(){
        string me = name;
        if (contains_item)
            me += "*";
        return me;
    }
    std::string get_prompt(){return "Open the chest?(y,n)";}
    std::string get_adjacent_dialog(){return "I can see a chest over there on the ground!";}

    bool contains_item;
    Item item_inside;
};

#endif