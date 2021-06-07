#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include <iostream>

class Item{
    public:
    Item(){;}
    int get_sellprice();
    virtual std::string get_string(){return name;}
    virtual void use(){}
    std::vector<std::string> tags;
    float rarity;
    std::string name;
};

Item* getRandomItem(float luck_factor=0.0);


#endif