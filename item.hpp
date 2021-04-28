#include <vector>
#include <string>
#include <iostream>

class Item{
    public:
    Item(){std::cout<<"making item"<<std::endl;}
    int get_sellprice();
    virtual std::string get_string(){return name;}
    virtual void use(){}
    std::vector<std::string> tags;
    float rarity;
    std::string name;
};

Item getRandomItem(float luck_factor);