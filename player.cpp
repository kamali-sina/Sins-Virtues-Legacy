#include "player.hpp"

using namespace std;

Player::Player() {
    location = pair<int,int>(0,0);
    hp = max_hp;
    equipped = new Fist();
    for (int i= 0 ; i < 7 ; i++)
        addItem(getRandomItem());
}

std::pair<int,int> Player::getLocation() {
    return location;
}

int Player::getCoins() {
    return coin;
}

void Player::deductCoins(int amount) {
    coin -= amount;
}

void Player::addCoins(int amount) {
    coin += amount;
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

int Player::getScraps() {
    return scrap;
}

void Player::deductScraps(int amount) {
    scrap -= amount;
}

void Player::addScraps(int amount) {
    scrap += amount;
}

bool Player::doesItemExist(Item* item) {
    for (auto& ite : inventory) {
        if (ite->getName() == item->getName()) {
            return true;
        }
    }
    return false;
}

void Player::scrapItem(int item_index) {
    AttackItem *attackitem = (AttackItem*)getItemAtIndex(item_index);
    addScraps(attackitem->getScrapParts());
    inventory.erase(inventory.begin() + item_index);
}

int Player::healWithItem(int item_index) {
    HpItem* hpitem = (HpItem*)getItemAtIndex(item_index);
    heal(hpitem->getHP());
    inventory.erase(inventory.begin() + item_index);
    return hp;
}

void Player::addItem(Item* item) {
    if (item->tagsContain(COINITEMTAG)) {
        CoinItem* coinitem = (CoinItem*)item;
        addCoins(coinitem->getAmount());
        gotXCoinsDialog(coinitem->getAmount());
        return;
    } else if (item->tagsContain(SCRAPITEMTAG)) {
        ScrapItem* scrapitem = (ScrapItem*)item;
        addScraps(scrapitem->getAmount());
        gotXScrapsDialog(scrapitem->getAmount());
        return;
    } else if (item->tagsContain(ATTACKITEMTAG) && doesItemExist(item)) {
        AttackItem* attackitem = (AttackItem*)item;
        addScraps(attackitem->getScrapParts());
        scrappedDuplicatieItemDialog(attackitem->getName(), attackitem->getScrapParts());
        return;
    }
    inventory.push_back(item);
    foundItemDialog(item->getName(), item->getColor());
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
    if (hp == max_hp) {
        hpIsNowFullDialog(hp);
    } else {
        hpIsNowDialog(hp);
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
    // TODO: print_affected_effects()
}

int Player::indexItem(std::string item_name) {
    for (int i = 0 ; i < inventory.size() ; i++ ) {
        if (inventory[i]->getName() == item_name)
            return i;
    }
    return -1;
}

int Player::getSpeed() {
    return equipped->getSpeed();
}

void Player::removeIfEquipped(int item_index) {
    Item* item = (Item*)equipped;
    if (inventory[item_index] == equipped) {
        equipped = new Fist();
    }
}

void Player::sellItem(int item_index) {
    int price = inventory[item_index]->getPlayerSellPrice();
    addCoins(price);
    removeIfEquipped(item_index);
    inventory.erase(inventory.begin() + item_index);
    soldItemDialog(price);
}

int Player::getPlayerSellPrice(int item_index) {
    Item* item = inventory[item_index];
    int price = item->getPlayerSellPrice();
    return price;
}

void Player::equipItem(Item* item) {
    equipped = (AttackItem*)item;
    equippedItemDialog(equipped->getName());
}

int Player::attack(std::string enemy_name) {
    int damage = equipped->getDamage();
    if (equipped->tagsContain(RANGEDATTACKITEMTAG)) {
        RangedAttackItem *ranged = (RangedAttackItem*) equipped;
        if (_random() < ranged->getMisschance()) {
            damage = 0;
        }
    }
    if (damage > 0) {
        attackedEnemyDialog(enemy_name, damage);
    } else {
        missedShotDialog();
    }
    return damage;
}