#include "player.hpp"

using namespace std;

Player::Player() {
    location = pair<int,int>(0,0);
    hp = max_hp;
}

std::pair<int,int> Player::getLocation() {
    return location;
}

void Player::setLocation(std::pair<int,int> new_location){
    location = new_location;
}

int Player::getDamaged(int damage) {
    hp -= damage;
    if (hp <= 0) {
        cout<<"YOU DIED!"<<endl;
        exit(0);
    }
    return hp;
}

void Player::addItem(Item* item){
    inventory.push_back(item);
    foundItemDialog(item->getName());
}

int Player::refillHP() {
    hp = max_hp; 
    return hp;
}
int Player::heal(int amount) {
    hp += amount; 
    return hp;
}