#include "player.hpp"

using namespace std;

Player::Player() {
    location = pair<int,int>(0,0);
    hp = max_hp;
}

std::pair<int,int> Player::getLocation() {
    return location;
}

void Player::setLocation(std::pair<int,int> new_location) {
    location = new_location;
}

Item* Player::getItemAtIndex(int index) {
    return inventory[index];
}

int Player::useSteroid() {
    max_hp += STEROID_HEALTH_UPGRADE;
    return refillHP();;
}

int Player::removeItem(int inventory_index) {
    inventory.erase(inventory.begin() + inventory_index);
}

void Player::useItem(int inventory_index) {
    UtilityItem* item = (UtilityItem*)getItemAtIndex(inventory_index);
    int isStillViable = item->use();
    if (isStillViable == 0) {
        removeItem(inventory_index);
        itemIsNoLongerUsableDialog(item->getName());
    }
}

int Player::getDamaged(int damage) {
    hp -= damage;
    if (hp <= 0) {
        deathDialog();
        exit(0);
    }
    return hp;
}

void Player::addItem(Item* item) {
    inventory.push_back(item);
    foundItemDialog(item->getName());
}

int Player::refillHP() {
    hp = max_hp; 
    return hp;
}
int Player::heal(int amount) {
    hp += amount; 
    if (hp > max_hp){
        hp = max_hp;
    }
    return hp;
}