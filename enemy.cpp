#include "enemy.hpp"

Guy::Guy() {
    name = "guy";
    hp = 1;
    bounty = 1;
    speed = 4;
    damage = 2;
    rarity = 4;
}

Wolf::Wolf() {
    name = "wolf";
    hp = 4;
    bounty = 2;
    speed = 7;
    damage = 3;
    rarity = 3;
}

BigBob::BigBob() {
    name = "bigBob";
    hp = 12;
    bounty = 2;
    speed = 5;
    damage = 6;
    rarity = 4;
}

Enemy* getEnemy(int enemy_id){
    switch (enemy_id) {
        case 1: return new Guy();
        case 2: return new Wolf();
        case 3: return new BigBob();
        case 4: ;
        case 5: ;
        case 6: ;
        default: return new Enemy();
    }
}

Enemy* getRandomEnemy(float difficulty_factor){
    int enemy_id = (rand() % NUMBER_OF_ENEMIES) + 1;
    return getEnemy(enemy_id);
}