#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "termcolor.hpp"
#include "dialogs.hpp"
#include "player.hpp"

// Deprecated
#define BASE_SPEED_TIME 1

// Difficulty scaling factors
#define HPSCALE 0.2
#define DAMAGESCALE 0.2

#define NUMBER_OF_ENEMIES 4
#define GUY 1
#define WOLF 2
#define BIGBOB 3
#define ROTTER 4

#define NUMBER_OF_BOSSES 1
#define FUJILA 1

class Enemy {
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
    virtual std::string serialize() { return std::to_string(id); }
    virtual void deserialize(std::vector<std::string> args) { return; }
    virtual void updateScaling(int days_passed);

    protected:
    void reduceHP(int _damage);
    std::string name = "";
    int hp = 0;
    int bounty = 0;
    int id = 0;
    float speed = 0;
    int damage = 0;
    float time_in_fight = 0;
    float rarity = 1;
};

class Boss: public Enemy {
    public:
    Boss() {}
    virtual std::string getIntroDialog() { return ""; }
};

class Guy: public Enemy {
    /*you can 'talk' with to end fight*/
    public:
    Guy();
};

class Wolf: public Enemy {
    /*can be given a single meat to end fight*/
    public:
    Wolf();
    
    std::string getKillDialog() {
        return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the wolf, how does a wolf have money?";
    }
};

class Rotter: public Enemy {
    public:
    Rotter();
    
    void attack(Player* player);
    private:
    float APPLY_CHANCE;
};

class BigBob: public Enemy {
    public:
    BigBob();
};

class Fujila: public Boss {
    public:
    Fujila();
    std::string getIntroDialog();
    int getDamaged(int _damage);

    private:
    int boost = 1;
};

Enemy* getEnemy(int enemy_id);
Enemy* getRandomEnemy(float difficulty_factor=0.0);
Boss* getBoss(int boss_id);
Boss* getRandomBoss(float difficulty_factor=0.0);

#endif