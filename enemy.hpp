#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "termcolor.hpp"

#define NUMBER_OF_ENEMIES 3

class Enemy{
    public:
    Enemy(){ }
    std::string getName() { return name; }
    int getHP() { return hp; }
    int getBounty() { return bounty; }
    float getSpeed() { return speed; }
    int getDamage() { return damage; }
    float getRarity() { return rarity; }
    virtual int getDamaged(int _damage){
        hp -= _damage;
        return hp;
    }

    virtual std::string getKillDialog(){
        return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the " + name;
    }

    protected:
    std::string name = "";
    int hp = 0;
    int bounty = 0;
    float speed = 0;
    int damage = 0;
    float rarity = 1;
};

class Guy: public Enemy{
    /*you can 'talk' with to end fight*/
    public:
    Guy(){ }
    std::string name = "guy";
    int hp = 1;
    int bounty = 1;
    float speed = 2;
    int damage = 2;
    float rarity = 4;
};

class Wolf: public Enemy{
    /*can be given a single meat to end fight*/
    public:
    Wolf(){ }

    std::string name = "wolf";
    int hp = 4;
    int bounty = 2;
    float speed = 7;
    int damage = 3;
    float rarity = 3;
    
    std::string getKillDialog(){
        return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the wolf, how does a wolf have money?";
    }
};

class BigBob: public Enemy{
    public:
    BigBob(){ }

    std::string name = "big_bob";
    int hp = 12;
    int bounty = 2;
    float speed = 3;
    int damage = 6;
    float rarity = 4;
};

Enemy* getEnemy(int enemy_id);
Enemy* getRandomEnemy(float difficulty_factor=0.0);

#endif