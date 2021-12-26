#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "item.hpp"
#include "dialogs.hpp"
#include "status_effect.hpp"
#include <vector>
#include <string>
#include <utility>
#include <fstream>

#define ITEM_WEIGHT_SOFT_THRESHHOLD 2
#define BASE_BLOCK_MOVE_TIME 0.26
#define EXTRA_TIME_PER_KG 0.05
#define STEROID_HEALTH_UPGRADE 5
#define GOLDEN_CARROT_VISION_UPGRADE 1

class Player {
    public:
    Player(bool dev_mode = false);
    int getDamaged(int damage);
    int getVision() { return vision; }
    int getMaxHp() { return max_hp; }
    Item* getItemAtIndex(int index);
    int getHP() { return hp; }
    int useSteroid();
    int useGoldenCarrot();
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
    int indexItem(int item_id);
    void equipItem(Item* item);
    void scrapItem(int item_index);
    int getSpeed();
    int healWithItem(int item_index);
    float getTotalWeight();
    std::pair<int,int> getLocation();
    int refillHP();
    int heal(int amount);
    void addItem(Item* item, bool silent=false);
    void addStatusEffect(StatusEffect* status, bool silent=false);
    void applyStatusEffects();
    void resetStatusEffectsList();
    int indexStatusEffect(std::string status_name);
    void resetStatusEffect(int status_index);

    void save(std::string path);
    void load(std::string path);

    protected:
    void printAffectedEffectsDescriptions();
    bool doesItemExist(Item* item);
    std::vector<Item*> inventory;
    std::vector<StatusEffect*> status_effects;
    int max_hp=10;
    int hp;
    int coin=0;
    int vision = 1;
    int scrap=0;
    std::pair<int,int> location;
    float time_in_fight = 0;
    AttackItem* equipped;
};

/* functions to add:
def add_status_effect:...

def update_status_effects(self):
    for i in range(len(self.status_effects) - 1, -1, -1):
        effect = self.status_effects[i]
        effect.apply(self)
        if effect.turns <= 0:
            self.status_effects.pop(i)
            print(f"status effect {effect} ended!")

def reset_status_effects(self):
    self.status_effects = []

# add to info
def print_affected_effects(self):
    for effect in self.status_effects:
        ConsoleHandler.notification(effect.description(), speed=20)

*/

// type check:
/*

template <class DstType, class SrcType>
bool IsType(const SrcType* src)
{
  return dynamic_cast<const DstType*>(src) != nullptr;
}

*/

#endif