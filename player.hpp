#include "item.hpp"
#include "dialogs.hpp"
#include <vector>
#include <string>
#include <utility>


class Player {
    public:
    Player();
    int getDamaged(int damage);
    int getMaxHp() { return max_hp; }
    void setLocation(std::pair<int,int> new_location);
    std::pair<int,int> getLocation();
    int refillHP();
    int heal(int amount);
    void addItem(Item* item);

    protected:
    std::vector<Item*> inventory;
    int max_hp=10;
    int hp;
    int coin=0;
    int scrap=0;
    std::pair<int,int> location;
    //TODO: set to fists
    Item* equipped;
};