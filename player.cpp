#include "player.hpp"

using namespace std;

Player::Player() {
    location = pair<int,int>(0,0);
    hp = max_hp;
    equipped = new Fist();
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

void Player::removeItem(int inventory_index) {
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
    //TODO: fix coins, duplicates and other stuff
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

void Player::printInventory() {
    if (inventory.size() == 0) {
        IHaveNoItemsDialog();
        return;
    }
    cout<<"==========Inventory=========="<<endl;
    cout<<"  name                 info  "<<endl;
    cout<<"-----------------------------"<<endl;
    for (Item* item : inventory) {
        cout<<" " << item->getString();
        int spaces = 22 - item->getName().length();
        for (int i = 0; i < spaces ; i++) cout<<" ";
        cout<< item->getInfo() << endl;
    }
}

void Player::printInfo() {
    cout<< colored("hp",GREEN) + ": " + to_string(hp) <<endl;
    cout<< colored("coins",YELLOW) + ": " + to_string(coin) <<endl;
    cout<< colored("scraps",BLACK) + ": " + to_string(scrap) <<endl;
    cout<< colored("location",BLUE) + ": [" + to_string(location.first) + "," + to_string(location.second) + "]" <<endl;
    cout<< colored("equipped item",WHITE) + ": " + equipped->getString() <<endl;
    cout<< to_string(inventory.size()) + " item(s) in " + colored("inventory",CYAN) <<endl;
    // TODO: self.print_affected_effects()
}

int Player::indexItem(std::string item_name) {
    for (int i = 0 ; i < inventory.size() ; i++ ) {
        if (inventory[i]->getName() == item_name)
            return i;
    }
    return -1;
}

void Player::equipItem(Item* item) {
    equipped = item;
    equippedItemDialog(equipped->getName());
}