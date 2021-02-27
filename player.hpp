#include "item.hpp"
#include <vector>
#include <string>
#include <utility>


class Player{
    public:
    std::vector<Item> inventory;
    int max_hp;
    int hp;
    int coin;
    std::pair<int,int> location;
    Item equipped;
};