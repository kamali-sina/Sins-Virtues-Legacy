#include "item.hpp"

using namespace std;

/* ==================== Base Class ==================== */

int Item::getSellprice() {
    float MAX = 0.80;
    float MIN = 0.60;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    return (int)(rarity * price_multiplier);
}

bool Item::tagsContain(std::string tag) {
    for (int i = 0 ; i < tags.size() ; i++) {
        if (tags[i] == tag) return true;
    }
    return false;
}

/* ==================== Coin ==================== */

CoinItem::CoinItem() {
    name = "coin";
    color = YELLOW;
    tags.push_back("coin");
    assignAmount();
}

void CoinItem::assignAmount() {
    amount = (int)((max_coins - min_coins + 1) * _random()) + min_coins;
}

std::string CoinItem::getInfo() { 
    return "amount: " + to_string(amount); 
}

/* ==================== Scrap ==================== */

ScrapItem::ScrapItem() {
    name = "scrap";
    color = BLACK;
    tags.push_back("scrap");
    assignAmount();
}

void ScrapItem::assignAmount() {
    amount = (int)((max_scraps - min_scraps + 1) * _random()) + min_scraps;
}

std::string ScrapItem::getInfo() { 
    return "amount: " + to_string(amount); 
}

/* ==================== Utility ==================== */

UtilityItem::UtilityItem() {
    name = "utility";
    color = BLUE;
    tags.push_back("utility");
    uses = initial_uses;
}

int UtilityItem::getSellprice() {
    float MAX = 0.80;
    float MIN = 0.60;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    float use_multiplier = (float)(uses) / (float)(initial_uses);
    return (int)(rarity * price_multiplier * use_multiplier);   
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

/* ==================== HP ==================== */

HpItem::HpItem() {
    name = "hp";
    color = GREEN;
    tags.push_back("hp");
}

std::string HpItem::getInfo() { 
    return "restores: " + to_string(hp) + "hp";
}

/* ==================== Attack ==================== */

AttackItem::AttackItem() {
    type = "none";
    tags.push_back("attack");
    color = RED;
    name = "attackItem";
}

std::string AttackItem::upgrade() {
    lvl += 1;
    damage += 1;
    return "upgraded!";
}

int AttackItem::getSellPrice() {
    float MAX = 0.80 + lvl * 0.3;
    float MIN = 0.60 + lvl * 0.3;
    float price_multiplier = (MAX - MIN) * _random() + MIN;
    return (int)(rarity * price_multiplier);
}

int AttackItem::getUpgradePrice() {
    float price_multiplier = 1 + ((float)lvl * 0.66);
    price_multiplier *= 0.25;
    return (int)(rarity * price_multiplier);
}

int AttackItem::getScrapParts() {
    float MAX = 1;
    float MIN = 0.8;
    float price_multiplier = (MAX - MIN) * random() + MIN;
    price_multiplier *= 1 + ((float)lvl / 3.0);
    price_multiplier *= 0.25;
    return (int)(rarity * price_multiplier);
}

std::string AttackItem::getInfo() {
    return "damage: " + to_string(damage) + ", speed: " + to_string(speed);
}

/* ==================== Melee ==================== */

MeleeAttackItem::MeleeAttackItem() {
    type = "melee";
    tags.push_back("attack");
    tags.push_back("melee");
    name = "meleeattackItem";
    rarity = 0;
}

std::string MeleeAttackItem::upgrade() {
    if (lvl >= 3) {
        return "Can't upgrade the weapon any further!";
    }
    lvl += 1;
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
    tags.push_back("attack");
    tags.push_back("ranged");
    name = "rangedattackItem";
    rarity = 0;
}

std::string RangedAttackItem::upgrade() {
    if (lvl >= 3) {
        return "Can't upgrade the weapon any further!";
    }
    lvl += 1;
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
    rarity = COMMON;
    tags.push_back(RANDOMTAG);
    tags.push_back("attack");
    name = "shovel";
    uses = initial_uses;
    id = 1;
    /*
        TODO:
        self.damage = 3
        self.speed = 4
    */
}


Compass::Compass() {
    initial_uses = 9999;
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "compass";
    uses = initial_uses;
    id = 2;
}

std::string Compass::getInfo() {
    return "infinite uses";
}


MapItem::MapItem() {
    initial_uses = 3;
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "map";
    uses = initial_uses;
    id = 3;
}


Steroid::Steroid() {
    initial_uses = 1;
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "steroid";
    uses = initial_uses;
    id = 4;
}

/* ==================== MeleeAttackItem Classes ==================== */

Fist::Fist() {
    rarity = 0;
    name = "fist";
    damage = 1;
    speed = 6;
    id = 5;
}


Knife::Knife() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    tags.push_back("utility");
    name = "knife";
    damage = 3;
    speed = 9;
    id = 6;
}


Sword::Sword() {
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "sword";
    damage = 7;
    speed = 6;
    id = 7;
}


Axe::Axe() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "sword";
    damage = 14;
    speed = 2;
    id = 8;
}

/* ==================== RangedAttackItem Classes ==================== */

Peacemaker::Peacemaker() {
    rarity = EPIC;
    tags.push_back(RANDOMTAG);
    name = "peacemaker";
    damage = 6;
    speed = 6;
    misschance = 0.2;
    id = 9;
}

Shotgun::Shotgun() {
    rarity = LEGENDARY;
    tags.push_back(RANDOMTAG);
    name = "shotgun";
    damage = 13;
    speed = 5;
    misschance = 0.3;
    id = SHOTGUN;
}

/* ==================== HpItem Classes ==================== */

Apple::Apple() {
    rarity = COMMON;
    tags.push_back(RANDOMTAG);
    name = "apple";
    hp = 3;
    id = 10;
}


Celery::Celery() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "celery";
    hp = 11;
    id = 11;
} 


Meat::Meat() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    name = "meat";
    hp = 6;
    id = 12;
} 

/* ==================== CoinItem Classes ==================== */

CoinStack::CoinStack() {
    rarity = UNCOMMON;
    tags.push_back(RANDOMTAG);
    name = "coinstack";
    min_coins = 2;
    max_coins = 4;
    assignAmount();
    id = 13;
}


CoinBag::CoinBag() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "coinbag";
    min_coins = 3;
    max_coins = 8;
    assignAmount();
    id = 14;
}

/* ==================== ScrapItem Classes ==================== */

ScrapBox::ScrapBox() {
    rarity = RARE;
    tags.push_back(RANDOMTAG);
    name = "scrapbox";
    min_scraps = 1;
    max_scraps = 3;
    assignAmount();
    id = 15;
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