#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "termcolor.hpp"
#include "dialogs.hpp"
#include "player.hpp"


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
    bool isDead() { return hp == 0; }
    virtual int getDamaged(int _damage);
    virtual void attack(Player* player);
    virtual std::string getInfo();
    virtual std::string getKillDialog();

    protected:
    void reduceHP(int _damage);
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