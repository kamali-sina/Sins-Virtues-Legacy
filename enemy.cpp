#include "enemy.hpp"

/* ==================== Base Class ==================== */

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

void Enemy::updateScaling(int days_passed) {
    float new_hp_scale = (HPSCALE * days_passed) + 1;
    float new_damage_scale = (DAMAGESCALE * days_passed) + 1;
    damage = new_damage_scale * damage;
    hp = new_hp_scale * hp;
}

/* ==================== Normal Enemy Classes ==================== */

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

/* ==================== Boss Enemy Classes ==================== */

Fujila::Fujila() {
    name = "fujila";
    hp = 20;
    bounty = 15;
    speed = 4;
    damage = 6;
    rarity = 3;
    id = FUJILA;
}

std::string Fujila::getIntroDialog() {
    return "I'm Fujila but my friends call me Fuj! Time to die!!!";
}

int Fujila::getDamaged(int _damage) {
    hp -= _damage;
    if (hp <= 10 && boost > 0) { 
        boost -= 1;
        fujilaBoostDialog();
        damage += 2;
        speed += 2;
    }
}

/* ==================== Spawners ==================== */

Enemy* getEnemy(int enemy_id) {
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

Enemy* getRandomEnemy(float difficulty_factor) {
    int enemy_id = (rand() % NUMBER_OF_ENEMIES) + 1;
    return getEnemy(enemy_id);
}


Boss* getBoss(int boss_id) {
    switch (boss_id) {
        case FUJILA: return new Fujila();
        case 2: ;
        case 3: ;
        case 4: ;
        case 5: ;
        case 6: ;
        default: return new Boss();
    }
}

Boss* getRandomBoss(float difficulty_factor=0.0) {
    int boss_id = (rand() % NUMBER_OF_BOSSES) + 1;
    return getBoss(boss_id);
}