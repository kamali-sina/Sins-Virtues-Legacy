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

#define ITEMCOUNT 16

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

/* ==================== Base Classes ==================== */

#define RANDOMTAG "random"
#define NOTBUYABLETAG "notbuyable"

class Item {
    public:
    Item() {;}
    virtual int getSellprice();
    std::string getName() { return name; }
    bool tagsContain(std::string tag);
    int getID() { return id; }
    int getRarity() { return rarity; }
    std::vector<std::string> getTags() { return tags; }
    std::string getString() { return colored(name, color); }
    std::string getColor() { return color; }
    virtual std::string getInfo() { return "infoBase"; }
    // virtual void use(){}

    protected:
    std::vector<std::string> tags;
    float rarity;
    int price;
    std::string name = "item";
    std::string color = WHITE;
    int id;
};

class CoinItem : public Item {
    public:
    CoinItem();
    void assignAmount();
    std::string getInfo();

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

    protected:
    int min_scraps = 0;
    int max_scraps = 0;
    int amount;
};

class UtilityItem : public Item {
    public:
    UtilityItem();
    std::string getInfo();
    int getSellprice();
    int getUsesRemaining() { return uses; }
    int use();

    protected:
    int initial_uses = 0;
    int uses;
};

class HpItem : public Item {
    public:
    HpItem();
    int getHP(){ return hp; };
    std::string getInfo();

    protected:
    int hp = 0;
};

class AttackItem : public Item {
    public:
    AttackItem();
    int getSpeed(){ return speed; }
    int getLvl(){ return lvl; }
    virtual std::string upgrade();
    int getSellPrice();
    int getUpgradePrice();
    int getScrapParts();
    std::string getInfo();

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
    int speed = 0;
    int damage = 0;
    std::string type;
    int lvl = 0;
};

class RangedAttackItem : public AttackItem {
    public:
    RangedAttackItem();
    std::string upgrade();
    std::string getInfo();

    protected:
    int speed = 0;
    int damage = 0;
    float misschance = 0.0;
    std::string type;
    int lvl = 0;
};

/* ==================== UtilityItem Classes ==================== */

class Shovel : public UtilityItem {
    public:
    Shovel();
};


class Compass : public UtilityItem {
    public:
    Compass();
    std::string getInfo();
};


class MapItem : public UtilityItem {
    public:
    MapItem();
};


class Steroid : public UtilityItem {
    public:
    Steroid();
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