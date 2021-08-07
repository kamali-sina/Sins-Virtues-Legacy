#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "termcolor.hpp"


#define BASE_SPEED_TIME 10
#define NUMBER_OF_ENEMIES 3
//TODO: FIX SPEEDS
class Enemy{
    public:
    Enemy() { }
    std::string getName() { return name; }
    int getHP() { return hp; }
    int getBounty() { return bounty; }
    float getSpeed() { return speed; }
    int getDamage() { return damage; }
    int getAttackTime() { return BASE_SPEED_TIME - speed; }
    float getRarity() { return rarity; }
    float getTimeInFight() { return time_in_fight; }
    void resetTimeInFight(float value = 0.0) { time_in_fight = value; }
    void updateTimeInFight(float value) { time_in_fight += value; }
    virtual int getDamaged(int _damage) {
        hp -= _damage;
        return hp;
    }
    virtual std::string getInfo() {
        return "name: " + name + "\nhp: " + std::to_string(hp) + "\nspeed: " + std::to_string(speed) + "\ndamage: " + std::to_string(damage);
    }
    virtual std::string getKillDialog() {
        return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the " + name;
    }

    protected:
    std::string name = "";
    int hp = 0;
    int bounty = 0;
    float speed = 0;
    int damage = 0;
    float time_in_fight = 0;
    float rarity = 1;
};

class Guy: public Enemy{
    /*you can 'talk' with to end fight*/
    public:
    Guy();
};

class Wolf: public Enemy{
    /*can be given a single meat to end fight*/
    public:
    Wolf();
    
    std::string getKillDialog() {
        return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the wolf, how does a wolf have money?";
    }
};

class BigBob: public Enemy{
    public:
    BigBob();
};

Enemy* getEnemy(int enemy_id);
Enemy* getRandomEnemy(float difficulty_factor=0.0);

#endif