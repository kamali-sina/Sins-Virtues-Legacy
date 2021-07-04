#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include <iostream>

class Item{
    public:
    Item(){;}
    int getSellprice();
    std::string getName(){ return name; }
    virtual std::string getString(){ return name; }
    virtual void use(){}

    protected:
    std::vector<std::string> tags;
    float rarity;
    std::string name = "item";
};

Item* getRandomItem(float luck_factor=0.0);


#endif