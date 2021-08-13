#ifndef _PLAYER_HPP
#define _PLAYER_HPP

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
    int getHP() { return hp; }
    int useSteroid();
    int getCoins();
    int attack(std::string enemy_name);
    int getScraps();
    void addScraps(int amount);
    void removeIfEquipped(int item_index);
    void deductScraps(int amount);
    void deductCoins(int amount);
    void addCoins(int amount);
    void sellItem(int item_index);
    int getPlayerSellPrice(int item_index);
    void updateTimeInFight(float value) { time_in_fight += value; }
    float getTimeInFight() { return time_in_fight; }
    void resetTimeInFight(float value = 0.0) { time_in_fight = value; }
    void removeItem(int inventory_index);
    void useItem(int inventory_index);
    void setLocation(std::pair<int,int> new_location);
    void printInventory();
    void printInfo();
    int indexItem(std::string item_name);
    void equipItem(Item* item);
    void scrapItem(int item_index);
    int getSpeed();
    int healWithItem(int item_index);
    std::pair<int,int> getLocation();
    int refillHP();
    int heal(int amount);
    void addItem(Item* item);

    protected:
    bool doesItemExist(Item* item);
    std::vector<Item*> inventory;
    int max_hp=10;
    int hp;
    int coin=0;
    int vision = 1;
    int scrap=0;
    float time_in_fight = 0;
    std::pair<int,int> location;
    AttackItem* equipped;
};

#endif