#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include <iostream>
#include "console_handler.hpp"

/* rarity system: common uncommon rare epic legendary */

#define COMMON 1
#define UNCOMMON 2
#define RARE 3
#define EPIC 4
#define LEGENDARY 5

/* ==================== Base Classes ==================== */

class Item {
    public:
    Item() {;}
    virtual int getSellprice();
    std::string getName() { return name; }
    int getID() { return id; }
    std::vector<std::string> getTags() { return tags; }
    std::string getString() { return colored(name, color); }
    std::string getColor() { return color; }
    virtual std::string getInfo() { return "infoBase"; }
    // virtual void use(){}

    protected:
    std::vector<std::string> tags;
    float rarity;
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


class Map : public UtilityItem {
    public:
    Map();
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

/*
TODO:
class CoinStack(CoinItem):
    def __init__(self):
        self.MAX = 2
        self.MIN = 4
        self.rarity = 5
        self.name = 'coin_stack'
        self.tags = ['coin', 'random']
        self.amount = int((self.MAX - self.MIN + 1) * random()) + self.MIN

class CoinBag(CoinItem):
    def __init__(self):
        self.MAX = 3
        self.MIN = 8
        self.rarity = 10
        self.name = 'coin_stack'
        self.tags = ['coin', 'random']
        self.amount = int((self.MAX - self.MIN + 1) * random()) + self.MIN

class ScrapBox(ScrapItem):
    def __init__(self):
        self.MAX = 1
        self.MIN = 3
        self.rarity = 8
        self.name = 'scrap_box'
        self.tags = ['scrap', 'random']
        self.amount = int((self.MAX - self.MIN + 1) * random()) + self.MIN
*/

Item* getRandomItem(float luck_factor=0.0);


#endif