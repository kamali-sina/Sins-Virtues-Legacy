#include "item.hpp"
#include "dialogs.hpp"
#include <vector>
#include <string>
#include <utility>

#define STEROID_HEALTH_UPGRADE 5

class Player {
    public:
    Player();
    int getDamaged(int damage);
    int getVision() { return vision; }
    int getMaxHp() { return max_hp; }
    Item* getItemAtIndex(int index);
    int useSteroid();
    void updateTimeInFight(float value) { time_in_fight += value; }
    void removeItem(int inventory_index);
    void useItem(int inventory_index);
    void setLocation(std::pair<int,int> new_location);
    void printInventory();
    void printInfo();
    int indexItem(std::string item_name);
    void equipItem(Item* item);
    std::pair<int,int> getLocation();
    int refillHP();
    int heal(int amount);
    void addItem(Item* item);

    protected:
    std::vector<Item*> inventory;
    int max_hp=10;
    int hp;
    int coin=0;
    int vision = 1;
    int scrap=0;
    float time_in_fight = 0;
    std::pair<int,int> location;
    Item* equipped;
};