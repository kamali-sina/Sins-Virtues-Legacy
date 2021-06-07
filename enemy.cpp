#include "enemy.hpp"


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

Enemy* getRandomBlock(){
    int enemy_id = (rand() % NUMBER_OF_ENEMIES) + 1;
    return getEnemy(enemy_id);
}