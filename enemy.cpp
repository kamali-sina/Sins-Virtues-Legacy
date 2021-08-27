#include "enemy.hpp"

int Enemy::getDamaged(int _damage) {
    reduceHP(_damage);
    return hp;
}

void Enemy::attack(Player* player) {
    player->getDamaged(damage);
    enemyAttacksYouDialog(name, damage);
    updateTimeInFight(player->getSpeed());
}

std::string Enemy::getInfo() {
    return "name: " + name + "\nhp: " + std::to_string(hp) + "\nspeed: " + std::to_string(speed) + "\ndamage: " + std::to_string(damage);
}

std::string Enemy::getKillDialog() {
    return "Found " + colored(std::to_string(bounty),YELLOW) + " coin(s) on the " + name;
}

void Enemy::reduceHP(int _damage) { 
    hp -= _damage;
    hp = std::max(0, hp);
}

Guy::Guy() {
    name = "guy";
    hp = 1;
    bounty = 1;
    speed = 4;
    damage = 2;
    rarity = 4;
    id = GUY;
}

Wolf::Wolf() {
    name = "wolf";
    hp = 4;
    bounty = 2;
    speed = 7;
    damage = 3;
    rarity = 3;
    id = WOLF;
}

BigBob::BigBob() {
    name = "bigBob";
    hp = 12;
    bounty = 2;
    speed = 5;
    damage = 6;
    rarity = 4;
    id = BIGBOB;
}

Enemy* getEnemy(int enemy_id){
    switch (enemy_id) {
        case GUY: return new Guy();
        case WOLF: return new Wolf();
        case BIGBOB: return new BigBob();
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