#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include <iostream>
#include "console_handler.hpp"

/* ==================== Base Classes ==================== */

class Item {
    public:
    Item() {;}
    virtual int getSellprice();
    std::string getName() { return name; }
    std::string getString() { return colored(name, color); }
    std::string getColor() { return color; }
    virtual std::string getInfo() { return "infoBase"; }
    // virtual void use(){}

    protected:
    std::vector<std::string> tags;
    float rarity;
    std::string name = "item";
    std::string color = WHITE;
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

/* ==================== Item Classes ==================== */


Item* getRandomItem(float luck_factor=0.0);


#endif