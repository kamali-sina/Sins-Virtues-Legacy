#include "item.hpp"
#include "VnS.hpp"

using namespace std;

/* ==================== Base Class ==================== */

Item::Item() {
}

int Item::rerollPrice() {
    float MAX = 1.1;
    float MIN = 0.81;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    sell_price = max((int)(price * price_multiplier), 1);
    return sell_price;
}

bool Item::tagsContain(std::string tag) {
    for (int i = 0 ; i < tags.size() ; i++) {
        if (tags[i] == tag) return true;
    }
    return false;
}

int Item::getPlayerSellPrice() {
    if (sell_price == 0) {
        rerollPrice();
    }
    float multip = 0.8;
    return max((int)(multip * sell_price), 1);
}

int Item::getSellPrice() {
    if (sell_price == 0) {
        rerollPrice();
    }
    return sell_price;
}

/* ==================== Coin ==================== */

CoinItem::CoinItem() {
    name = "coin";
    color = YELLOW;
    tags.push_back(COINITEMTAG);
    assignAmount();
}

void CoinItem::assignAmount() {
    amount = (int)((max_coins - min_coins + 1) * _random()) + min_coins;
}

std::string CoinItem::getInfo() { 
    return "amount: " + to_string(amount); 
}

std::string CoinItem::serialize() {
    string serialized_data = to_string(id) + " " + to_string(amount);
    return serialized_data;
}

void CoinItem::deserialize(std::vector<std::string> args) {
    amount = stoi(args[1]);
}

/* ==================== Scrap ==================== */

ScrapItem::ScrapItem() {
    name = "scrap";
    color = BLACK;
    tags.push_back(SCRAPITEMTAG);
    assignAmount();
}

void ScrapItem::assignAmount() {
    amount = (int)((max_scraps - min_scraps + 1) * _random()) + min_scraps;
}

std::string ScrapItem::getInfo() { 
    return "amount: " + to_string(amount); 
}

std::string ScrapItem::serialize() {
    string serialized_data = to_string(id) + " " + to_string(amount);
    return serialized_data;
}

void ScrapItem::deserialize(std::vector<std::string> args) {
    amount = stoi(args[1]);
}

/* ==================== Utility ==================== */

UtilityItem::UtilityItem() {
    name = "utility";
    color = BLUE;
    tags.push_back(UTILITYITEMTAG);
    uses = initial_uses;
}

int UtilityItem::rerollPrice() {
    float MAX = 1.1;
    float MIN = 0.8;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    float use_multiplier = (float)(uses) / (float)(initial_uses);
    sell_price = (int)(price * price_multiplier * use_multiplier);
    return sell_price;
}

std::string UtilityItem::getInfo() { 
    return "uses remaining: " + to_string(uses);
}

int UtilityItem::use() {
    uses -= 1;
    if (uses <= 0)
        return 0;
    return 1;
}

std::string UtilityItem::serialize() {
    string serialized_data = to_string(id) + " " + to_string(uses);
    return serialized_data;
}

void UtilityItem::deserialize(std::vector<std::string> args) {
    uses = stoi(args[1]);
}

/* ==================== HP ==================== */

HpItem::HpItem() {
    name = "hp";
    color = GREEN;
    tags.push_back(HPITEMTAG);
}

std::string HpItem::getInfo() { 
    return "restores: " + to_string(hp) + "hp";
}

std::string HpItem::serialize() {
    string serialized_data = to_string(id);
    return serialized_data;
}

void HpItem::deserialize(std::vector<std::string> args) {
    
}

/* ==================== Attack ==================== */

AttackItem::AttackItem() {
    type = "none";
    tags.push_back(ATTACKITEMTAG);
    color = RED;
    name = "attackItem";
}

std::string AttackItem::upgrade() {
    lvl += 1;
    damage += 1;
    rerollPrice();
    return "upgraded!";
}

int AttackItem::rerollPrice() {
    float MAX = 1.2 + lvl * 0.3;
    float MIN = 1.0 + lvl * 0.3;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    sell_price = max((int)(price * price_multiplier), 1);
    return sell_price;
}

int AttackItem::getUpgradePrice() {
    float price_multiplier = 1 + ((float)lvl * 0.66);
    price_multiplier *= 0.25;
    return max((int)(price * price_multiplier), 1);
}

int AttackItem::getScrapParts() {
    float price_multiplier = 0.9;
    price_multiplier *= 1.0 + ((float)lvl / 3.0);
    price_multiplier *= 0.25;
    return max((int)(price * price_multiplier), 1);
}

std::string AttackItem::getInfo() {
    return "damage: " + to_string(damage) + ", speed: " + to_string(speed);
}

std::string AttackItem::serialize() {
    string serialized_data = to_string(id) + " " + to_string(lvl);
    return serialized_data;
}

void AttackItem::deserialize(std::vector<std::string> args) {
    int saved_level = stoi(args[1]);
    for (int i = 0 ; i < saved_level ; i++) {
        cout <<this->upgrade() << endl;
    }    
}

/* ==================== Melee ==================== */

MeleeAttackItem::MeleeAttackItem() {
    type = "melee";
    tags.push_back(ATTACKITEMTAG);
    tags.push_back("melee");
    name = "meleeattackItem";
    rarity = 0;
}

std::string MeleeAttackItem::upgrade() {
    if (lvl >= 3) {
        return "Can't upgrade the weapon any further!";
    }
    lvl += 1;
    rerollPrice();
    float up;
    switch(lvl) {
        case 1:
            up = (float)damage * 0.2;
            damage += (int)(up) + 1;
            return "Upgraded the blade, It now deals +20% damage";
        case 2:
            up = (float)speed * 0.15;
            speed += (int)(up) + 1;
            return "Upgraded the grip, It now has +15% speed";
        case 3:
            up = (float)damage * 0.3;
            damage += (int)(up) + 1;
            return "Upgraded the blade even further, It now deals +30% damage";
        default:
            return "An error has accrued!";
    }
}

std::string MeleeAttackItem::getInfo() {
    return "level: " + to_string(lvl) + ", damage: " + to_string(damage) + ", speed: " + to_string(speed) + ", type: " + type;
}

/* ==================== Ranged ==================== */

RangedAttackItem::RangedAttackItem() {
    type = "ranged";
    tags.push_back(ATTACKITEMTAG);
    tags.push_back(RANGEDATTACKITEMTAG);
    name = RANGEDATTACKITEMTAG;
    rarity = 0;
}

std::string RangedAttackItem::upgrade() {
    if (lvl >= 3) {
        return "Can't upgrade the weapon any further!";
    }
    lvl += 1;
    rerollPrice();
    float up;
    switch(lvl) {
        case 1:
            up = (float)damage * 0.15;
            damage += (int)(up) + 1;
            return "Upgraded the bullet material, It now deals +15% damage";
        case 2:
            up = (float)speed * 0.2;
            speed += (int)(up) + 1;
            return "Upgraded the trigger, It now has +20% speed";
        case 3:
            misschance = misschance / 2;
            return "Added a new and improved sight, It now has -50% misschance";
        default:
            return "An error has accrued!";
    }
}

std::string RangedAttackItem::getInfo() {
    return "level: " + to_string(lvl) + ", damage: " + to_string(damage) + ", speed: " + to_string(speed) + ", type: " + type + ", misschance: " + to_string((misschance*100)) + "%";
}

/* ==================== UtilityItem Classes ==================== */

Shovel::Shovel() {
    initial_uses = 4;
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    // tags.push_back(ATTACKITEMTAG);
    name = "shovel";
    uses = initial_uses;
    price = 4;
    id = SHOVEL;
    weight = 2;
    /*
        TODO:
        self.damage = 3
        self.speed = 4
    */
}

void Shovel::use_item(int inventory_index) {
    session.digHere(inventory_index);
}


Compass::Compass() {
    initial_uses = 9999;
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "compass";
    price = 9;
    uses = initial_uses;
    id = COMPASS;
    weight = 0.2;
}

std::string Compass::getInfo() {
    return "infinite uses";
}

void Compass::use_item(int inventory_index) {
    cout<<session.getMap()->compass(session.getPlayer()->getLocation())<<endl;
}


MapItem::MapItem() {
    initial_uses = 3;
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "map";
    price = 7;
    uses = initial_uses;
    id = MAP;
    weight = 0.4;
}

void MapItem::use_item(int inventory_index) {
    session.getMap()->printPartialMap(
                                    session.getPlayer()->getVision(), 
                                    session.getPlayer()->getLocation()
                                    );
    session.getPlayer()->useItem(inventory_index);
}


Steroid::Steroid() {
    initial_uses = 1;
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "steroid";
    uses = initial_uses;
    price = 13;
    id = STEROID;
    weight = 0.5;
}

void Steroid::use_item(int inventory_index) {
    int new_max = session.getPlayer()->useSteroid();
    usedSteroidDialog(new_max);
    session.getPlayer()->useItem(inventory_index);
}


GoldenCarrot::GoldenCarrot() {
    initial_uses = 1;
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "goldencarrot";
    uses = initial_uses;
    price = 12;
    id = GOLDENCARROT;
    weight = 0.6;
}

void GoldenCarrot::use_item(int inventory_index) {
    int new_max = session.getPlayer()->useGoldenCarrot();
    usedGoldenCarrotDialog();
    session.getPlayer()->useItem(inventory_index);
}

/* ==================== MeleeAttackItem Classes ==================== */

Fist::Fist() {
    tags.push_back(NOTBUYABLETAG);
    rarity = 0;
    name = "fist";
    damage = 1;
    speed = 6;
    price = 0;
    id = 5;
    weight = 0;
}


Knife::Knife() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    tags.push_back("utility");
    name = "knife";
    damage = 3;
    speed = 9;
    price = 7;
    id = 6;
    weight = 1.5;
}


Sword::Sword() {
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "sword";
    damage = 7;
    speed = 5;
    price = 13;
    id = 7;
    weight = 3.9;
}


Axe::Axe() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "axe";
    damage = 12;
    speed = 3;
    price = 8;
    id = 8;
    weight = 13.0;
}

/* ==================== RangedAttackItem Classes ==================== */

Peacemaker::Peacemaker() {
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "peacemaker";
    damage = 6;
    speed = 6;
    price = 14;
    misschance = 0.2;
    id = 9;
    weight = 1.1;
}

Shotgun::Shotgun() {
    rarity = LEGENDARY;
    tags.push_back(RANDOMTAG);
    name = "shotgun";
    damage = 13;
    speed = 5;
    price = 18;
    misschance = 0.3;
    id = SHOTGUN;
    weight = 3.6;
}

/* ==================== HpItem Classes ==================== */

Apple::Apple() {
    rarity = COMMON;
    tags.push_back(RANDOMTAG);
    name = "apple";
    price = 2;
    hp = 3;
    id = 10;
    weight = 0.2;
}


Celery::Celery() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "celery";
    hp = 11;
    price = 7;
    id = 11;
    weight = 0.2;
} 


Meat::Meat() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    name = "meat";
    hp = 6;
    price = 5;
    id = 12;
    weight = 0.3;
} 

/* ==================== CoinItem Classes ==================== */

CoinStack::CoinStack() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    tags.push_back(NOTBUYABLETAG);
    name = "coinstack";
    min_coins = 2;
    max_coins = 4;
    assignAmount();
    id = 13;
    weight = 0.5;
}


CoinBag::CoinBag() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    tags.push_back(NOTBUYABLETAG);
    name = "coinbag";
    min_coins = 3;
    max_coins = 8;
    assignAmount();
    id = 14;
    weight = 1;
}

/* ==================== ScrapItem Classes ==================== */

ScrapBox::ScrapBox() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "scrapbox";
    min_scraps = 1;
    price = 9;
    max_scraps = 3;
    assignAmount();
    id = 15;
    weight = 1.5;
}

/* ==================== Item Generation ==================== */

Item *getItem(int item_id) {
    vector<Item*> all_items;
    all_items.push_back(new Shovel());
    all_items.push_back(new Compass());
    all_items.push_back(new MapItem());
    all_items.push_back(new Steroid());
    all_items.push_back(new Fist());
    all_items.push_back(new Knife());
    all_items.push_back(new Sword());
    all_items.push_back(new Axe());
    all_items.push_back(new Peacemaker());
    all_items.push_back(new Apple());
    all_items.push_back(new Celery());
    all_items.push_back(new Meat());
    all_items.push_back(new CoinStack());
    all_items.push_back(new CoinBag());
    all_items.push_back(new ScrapBox());
    all_items.push_back(new Shotgun());
    all_items.push_back(new GoldenCarrot());
    return all_items[item_id - 1];
}

int getRandomItemID() {
    return (rand() % ITEMCOUNT) + 1;
}

Item* getRandomItemWithRarity(int rarity) {
    int item_id = getRandomItemID();
    Item *random_item = getItem(item_id);
    while (random_item->getRarity() != rarity || !random_item->tagsContain(RANDOMTAG)) {
        int item_id = getRandomItemID();
        random_item = getItem(item_id);
    }
    return random_item;
}

int getRandomRarity() {
    vector<int> rarities({COMMON, UNCOMMON, RARE, EPIC, LEGENDARY});
    int sum = 0;
    for (auto& n : rarities)
        sum += n;
    int guess = (rand() % sum) + 1;
    for (auto& rarity : rarities) {
        if (guess <= rarity) return rarity;
        guess -= rarity;
    }
    return LEGENDARY;
}

Item* getRandomItem(float luck_factor) {
    int rarity = getRandomRarity();
    return getRandomItemWithRarity(rarity);
}