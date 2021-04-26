#include "item.hpp"
#include <vector>
#include <string>
#include <utility>


class Player{
    public:
    Player();
    int getDamaged(int damage);
    int getMaxHp(){return max_hp;}
    protected:
    std::vector<Item> inventory;
    int max_hp=10;
    int hp;
    int coin=0;
    int scrap=0;
    std::pair<int,int> location;
    //TODO: set to fizst
    Item equipped;
};