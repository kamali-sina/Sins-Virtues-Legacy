#include "player.hpp"

using namespace std;

Player::Player(bool dev_mode) {
    location = pair<int,int>(0,0);
    hp = max_hp;
    equipped = new Fist();
    addItem((Item*)new Notepad(), true);
    if (dev_mode) {
        cout << "how many items should be added? " << endl;
        int count;
        cin >> count;
        for (int i= 0 ; i < count ; i++)
            addItem(getRandomItem(), true);
    }
}

std::pair<int,int> Player::getLocation() {
    return location;
}

int Player::getCoins() {
    return coin;
}

float Player::getTotalWeight() {
    float total_weight = 0;
    for (Item* item : inventory){
        total_weight += item->getWeight();
    }
    return total_weight;
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

int Player::useGoldenCarrot() {
    vision += GOLDEN_CARROT_VISION_UPGRADE;
    return vision;
}

void Player::removeItem(int inventory_index) {
    removeIfEquipped(inventory_index);
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
    removeItem(item_index);
}

int Player::healWithItem(int item_index) {
    HpItem* hpitem = (HpItem*)getItemAtIndex(item_index);
    heal(hpitem->getHP());
    removeItem(item_index);
    return hp;
}

void Player::addItem(Item* item, bool silent) {
    if (item->tagsContain(COINITEMTAG)) {
        CoinItem* coinitem = (CoinItem*)item;
        addCoins(coinitem->getAmount());
        if (!silent)
            gotXCoinsDialog(coinitem->getAmount());
        return;
    } else if (item->tagsContain(SCRAPITEMTAG)) {
        ScrapItem* scrapitem = (ScrapItem*)item;
        addScraps(scrapitem->getAmount());
        if (!silent)
            gotXScrapsDialog(scrapitem->getAmount());
        return;
    } else if (item->tagsContain(ATTACKITEMTAG) && doesItemExist(item)) {
        AttackItem* attackitem = (AttackItem*)item;
        addScraps(attackitem->getScrapParts());
        if (!silent)
            scrappedDuplicatieItemDialog(attackitem->getName(), attackitem->getScrapParts());
        return;
    }
    inventory.push_back(item);
    if (!silent)
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
    float total_weight = getTotalWeight();
    cout<<"==========Inventory=========="<<endl;
    cout<<"  name                 info  "<<endl;
    cout<<"-----------------------------"<<endl;
    for (Item* item : inventory) {
        cout<<" " << item->getString();
        int spaces = 22 - item->getName().length();
        for (int i = 0; i < spaces ; i++) cout<<" ";
        cout<< item->getInfo() << endl;
    }
    cout<<"==========" << total_weight <<"KG=========="<<endl;
}

void Player::printInfo() {
    cout<< colored("hp", GREEN) + ": " + to_string(hp) <<endl;
    cout<< colored("coins", YELLOW) + ": " + to_string(coin) <<endl;
    cout<< colored("scraps", BLACK) + ": " + to_string(scrap) <<endl;
    cout<< colored("location", BLUE) + ": [" + to_string(location.first) + "," + to_string(location.second) + "]" <<endl;
    cout<< colored("equipped item", WHITE) + ": " + equipped->getString() <<endl;
    cout<< to_string(inventory.size()) + " item(s) in " + colored("inventory", CYAN) <<endl;
    // TODO: print_affected_effects()
}

int Player::indexItem(std::string item_name) {
    for (int i = 0 ; i < inventory.size() ; i++ ) {
        if (inventory[i]->getName() == item_name)
            return i;
    }
    return -1;
}

int Player::indexItem(int item_id) {
    for (int i = 0 ; i < inventory.size() ; i++ ) {
        if (inventory[i]->getID() == item_id)
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
    removeItem(item_index);
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

void Player::save(string path) {
    string player_items_path = path + PLAYERSAVEFILENAME;
    string notepad_path = path + NOTEPADSAVEFILENAME;
    ofstream file_obj;
    file_obj.open(player_items_path);
    file_obj << max_hp << endl;
    file_obj << hp << endl;
    file_obj << coin << endl;
    file_obj << vision << endl;
    file_obj << scrap << endl;
    file_obj << location.first << " " << location.second << endl;
    int equipped_index = indexItem(equipped->getName());
    file_obj << equipped_index << endl;
    for (auto& item : inventory) {
        file_obj<< item->serialize() << endl;
    }
    file_obj.close();
    ((Notepad*)getItemAtIndex(indexItem(NOTEPAD)))->save(notepad_path);
}

void Player::load(string path) {
    string player_items_path = path + PLAYERSAVEFILENAME;
    string notepad_path = path + NOTEPADSAVEFILENAME;
    ifstream file_obj;
    file_obj.open(player_items_path);
    inventory.clear();
    string line;
    file_obj >> max_hp;
    file_obj >> hp;
    file_obj >> coin;
    file_obj >> vision;
    file_obj >> scrap;
    int x, y;
    file_obj >> x >> y;
    location = pair<int,int>(x,y);
    vector<string> splitted_line;
    int equipped_index;
    file_obj >> equipped_index;
    while (getline(file_obj, line)) {
        if (line.size() == 0) continue;
        splitted_line = split_string(line, ' ');
        int item_id = stoi(splitted_line[0]);
        Item* item = getItem(item_id);
        item->deserialize(splitted_line);
        inventory.push_back(item);
    }
    if (equipped_index != -1) {
        equipped = (AttackItem*)inventory[equipped_index];
    }
    file_obj.close();
    ((Notepad*)getItemAtIndex(indexItem(NOTEPAD)))->load(notepad_path);
}