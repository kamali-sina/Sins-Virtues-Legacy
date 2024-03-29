#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include <iostream>
#include "console_handler.hpp"

/* rarity system: common uncommon rare epic legendary */

#define COMMON 50
#define UNCOMMON 29
#define RARE 15
#define EPIC 5
#define LEGENDARY 1

/* ==================== Item Class IDs ==================== */

/*
In case of adding a new item, add these to the following locations:
    1- Add the defined ID under here and update number of items
    2- Add the item to the end of the vector in getItem() function
    3- If needed add handler for block at handlers.hpp
*/

#define ITEMCOUNT 18

#define SHOVEL 1
#define COMPASS 2
#define MAP 3
#define STEROID 4
#define FIST 5
#define KNIFE 6
#define SWORD 7
#define AXE 8
#define PEACEMAKER 9
#define APPLE 10
#define CELERY 11
#define MEAT 12
#define COINSTACK 13
#define COINBAG 14
#define SCRAPBOX 15
#define SHOTGUN 16
#define GOLDENCARROT 17
#define NOTEPAD 18

/* ==================== Base Classes ==================== */

#define RANDOMTAG "random"
#define NOTBUYABLETAG "notbuyable"
#define NOTSELLABLETAG "notsellable"
#define ATTACKITEMTAG "attack"
#define RANGEDATTACKITEMTAG "rangedattackItem"
#define COINITEMTAG "coin"
#define SCRAPITEMTAG "scrap"
#define UTILITYITEMTAG "utility"
#define HPITEMTAG "hp"

#define ATTACKITEMMAXLEVEL 3

class Item {
    public:
    Item();
    virtual int rerollPrice();
    int getSellPrice();
    int getPlayerSellPrice();
    std::string getName() { return name; }
    bool tagsContain(std::string tag);
    int getID() { return id; }
    int getRarity() { return rarity; }
    float getWeight() { return weight; }
    std::vector<std::string> getTags() { return tags; }
    std::string getString() { return colored(name, color); }
    std::string getColor() { return color; }
    virtual std::string serialize() { return "this shoud not be called!"; }
    virtual void deserialize(std::vector<std::string> args) { return; }
    virtual std::string getInfo() { return "infoBase"; }

    protected:
    std::vector<std::string> tags;
    float rarity;
    int price = -1;
    int sell_price = 0;
    std::string name = "item";
    std::string color = WHITE;
    float weight = 0.0;
    int id;
};

class CoinItem : public Item {
    public:
    CoinItem();
    void assignAmount();
    std::string getInfo();
    int getAmount() { return amount; }
    std::string serialize();
    void deserialize(std::vector<std::string> args);
    protected:
    int min_coins = 0;
    int max_coins = 0;
    int amount;
};

class ScrapItem : public Item {
    public:
    ScrapItem();
    void assignAmount();
    std::string getInfo();
    int getAmount() { return amount; }
    std::string serialize();
    void deserialize(std::vector<std::string> args);

    protected:
    int min_scraps = 0;
    int max_scraps = 0;
    int amount;
};

class UtilityItem : public Item {
    public:
    UtilityItem();
    std::string getInfo();
    int rerollPrice();
    int getUsesRemaining() { return uses; }
    virtual void use_item(int inventory_index) = 0;
    int use();
    std::string serialize();
    void deserialize(std::vector<std::string> args);

    protected:
    int initial_uses = 0;
    int uses;
};

class HpItem : public Item {
    public:
    HpItem();
    int getHP(){ return hp; };
    std::string getInfo();
    std::string serialize();
    void deserialize(std::vector<std::string> args);

    protected:
    int hp = 0;
};

class AttackItem : public Item {
    public:
    AttackItem();
    int getSpeed(){ return speed; }
    int getLvl(){ return lvl; }
    int getDamage() { return damage; }
    virtual std::string upgrade();
    int rerollPrice();
    int getUpgradePrice();
    int getScrapParts();
    std::string getInfo();
    std::string serialize();
    void deserialize(std::vector<std::string> args);

    protected:
    int speed = 0;
    int damage = 0;
    std::string type;
    int lvl = 0;
};

class MeleeAttackItem : public AttackItem {
    public:
    MeleeAttackItem();
    std::string upgrade();
    std::string getInfo();

    protected:
};

class RangedAttackItem : public AttackItem {
    public:
    RangedAttackItem();
    float getMisschance() { return misschance; }
    std::string upgrade();
    std::string getInfo();

    protected:
    float misschance = 0.0;
};

/* ==================== UtilityItem Classes ==================== */

class Shovel : public UtilityItem {
    public:
    Shovel();
    void use_item(int inventory_index);
};


class Compass : public UtilityItem {
    public:
    Compass();
    void use_item(int inventory_index);
    std::string getInfo();
};


class MapItem : public UtilityItem {
    public:
    MapItem();
    void use_item(int inventory_index);
};


class Steroid : public UtilityItem {
    public:
    Steroid();
    void use_item(int inventory_index);
};

class GoldenCarrot : public UtilityItem {
    public:
    GoldenCarrot();
    void use_item(int inventory_index);
};

class Notepad : public UtilityItem {
    public:
    Notepad();
    void use_item(int inventory_index);
    std::string getInfo();
    void addEntry(std::string blockname, std::string blockcolor, std::pair<int,int> location);
    void save(std::string path);
    void load(std::string path);

    private:
    bool entryIsDuplicate(std::string blockname, std::pair<int,int> location);
    std::vector<std::string> names;
    std::vector<std::string> colors;
    std::vector<std::pair<int,int> > locations;
};

/* ==================== MeleeAttackItem Classes ==================== */

class Fist : public MeleeAttackItem {
    public:
    Fist();
};


class Knife : public MeleeAttackItem {
    public:
    Knife();
};


class Sword : public MeleeAttackItem {
    public:
    Sword();
};


class Axe : public MeleeAttackItem {
    public:
    Axe();
};

/* ==================== RangedAttackItem Classes ==================== */

class Peacemaker : public RangedAttackItem {
    public:
    Peacemaker();
};

class Shotgun : public RangedAttackItem {
    public:
    Shotgun();
};

/* ==================== HpItem Classes ==================== */

class Apple : public HpItem {
    public:
    Apple();
};


class Celery : public HpItem {
    public:
    Celery();
};


class Meat : public HpItem {
    public:
    Meat();
};

/* ==================== CoinItem Classes ==================== */

class CoinStack : public CoinItem {
    public:
    CoinStack();
};


class CoinBag : public CoinItem {
    public:
    CoinBag();
};

/* ==================== ScrapItem Classes ==================== */

class ScrapBox : public ScrapItem {
    public:
    ScrapBox();
};

/* ==================== Item Generation ==================== */

int getRandomRarity();
Item *getItem(int item_id);
Item* getRandomItem(float luck_factor=0.0);


#endif