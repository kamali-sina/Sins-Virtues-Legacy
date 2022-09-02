#include "commands.hpp"
#include "VnS.hpp"

using namespace std;

template <typename T>
int index_item(std::vector<T> list, T to_be_found) {
   for (int i = 0 ; i < list.size() ; i++) {
       if (list[i] == to_be_found) return i;
   }
   return NOTFOUND;
}

/* ============= Base Class ============== */

Command::Command() {
    command = "";
    args = vector<string>({"arg1", "arg2"});
    scopes.push_back(NORMAL);
    description = "base command that is going to be devrived!";
    dev_command = false;
    command_time = 0.0;
}

bool Command::isInScope(int givenScope) {
    for (auto scope : scopes) {
        if (scope == ALL) return true;
        if (scope == givenScope) return true;
    }
    return false;
}

bool Command::isDevOnly() {
    return dev_command;
}

void Command::commence(std::vector<std::string> splitted_input) {
    cout<< "base commence was called!" << endl;
}

/* ============= Commands ============== */

C_move::C_move() {
    command = "move";
    args = vector<string>({"direction"});
    scopes.push_back(NORMAL);
    description = "move around the map";
    dev_command = false;
}

void C_move::commence(std::vector<std::string> splitted_input) {
    vector<string> moveset({"north", "south", "east", "west", "up", "down", "left", "right"});
    vector<pair<int,int> > moveset_handler({pair<int,int>(1,0), pair<int,int>(-1,0), pair<int,int>(0,1), pair<int,int>(0,-1),
         pair<int,int>(1,0), pair<int,int>(-1,0), pair<int,int>(0,-1), pair<int,int>(0,1)});
    int index = index_item<string>(moveset, splitted_input[1]);
    if (index == NOTFOUND){
        _error("command is invalid!");
        return;
    }
    pair<int,int> new_location(session.player->getLocation().first + moveset_handler[index].first,
        session.player->getLocation().second + moveset_handler[index].second);
    if (!session.map->isLocationValid(new_location)){
        outOfBoundsDialog();
        return;
    }
    session.player->setLocation(new_location);
    // TODO: HANDLE IN GAME::: session.updateWorldTimer() should be called after commands
    session.can_spawn_enemy = true;
    session.handleNewReachedBlock();
}

float C_move::getCommandTime() {
    return session.getPlayerMoveTime();
}

/* ===================================== */

C_inventory::C_inventory() {
    command = "inventory";
    args = vector<string>();
    scopes.push_back(ALL);
    description = "view the contents of your inventory";
    dev_command = false;
    command_time = 0.15;
}

void C_inventory::commence(std::vector<std::string> splitted_input) {
    session.player->updateTimeInFight(0.5);
    session.player->printInventory();
    session.can_spawn_enemy = true;
}

/* ===================================== */

C_use::C_use() {
    command = "use";
    args = vector<string>({"item name"});
    scopes.push_back(ALL);
    description = "use an item";
    dev_command = false;
    command_time = 0.2;
}

void C_use::commence(std::vector<std::string> splitted_input) {
    int item_index = session.player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    Item* item = session.player->getItemAtIndex(item_index);
    session.updateWorldTimer(0.1);
    if (item->tagsContain(UTILITYITEMTAG)) {
        UtilityItem* utility_item = (UtilityItem*) item;
        utility_item->use_item(item_index);
    } else if (item->tagsContain(HPITEMTAG)) {
        session.player->healWithItem(item_index);
    } else {
        cantUseItemDialog();
        return;
    }
    session.player->updateTimeInFight(1.0);
}

/* ===================================== */

C_info::C_info() {
    command = "info";
    args = vector<string>();
    scopes.push_back(ALL);
    description = "get the general info of the game";
    dev_command = false;
    command_time = 0.1;
}

void C_info::commence(std::vector<std::string> splitted_input) {
    cout<<"========== Day " + to_string(session.days_passed) + " ==========" <<endl<<endl;
    session.player->printInfo();
    cout << "time: " << session.getClockTime() << endl;
    if (session.state == NORMAL){
        cout << "current block is " << colored(session.getBlockAtPlayerLocation()->getName(), MAGENTA) << endl;
    } else if (session.state == FIGHT) {
        cout<< "enemy has " << colored(to_string(session.enemy_fighting->getHP()), RED) << "hp left" << endl;
    }
    session.player->printAffectedEffectsDescriptions();
}

/* ===================================== */

C_commands::C_commands() {
    command = "commands";
    args = vector<string>();
    scopes.push_back(ALL);
    description = "you are currently using this";
    dev_command = false;
    command_time = 0.0;
}

void C_commands::commence(std::vector<std::string> splitted_input) {
    cout<< "Available commands:" << endl;
    for (auto& command : session.all_commands) {
        if (session.isCommandAvailable(command)) {
            cout<< "              " << colored("-", CYAN) << command.getCommand() << ": " << command.getDescription() << endl;
        }
    }
}

/* ===================================== */

C_dev_print_map::C_dev_print_map() {
    command = "print_map";
    args = vector<string>();
    scopes.push_back(NORMAL);
    description = "dev-only | print partial map";
    dev_command = true;
    command_time = 0.0;
}

void C_dev_print_map::commence(std::vector<std::string> splitted_input) {
    session.map->printPartialMap(2, session.player->getLocation());
}

// /* ===================================== */

C_dev_map::C_dev_map() {
    command = "map";
    args = vector<string>();
    scopes.push_back(NORMAL);
    description = "dev-only | print full map";
    dev_command = true;
    command_time = 0.0;
}

void C_dev_map::commence(std::vector<std::string> splitted_input) {
    session.map->printFullMap();
}

/* ===================================== */

C_equip::C_equip() {
    command = "equip";
    args = vector<string>({"item name"});
    scopes.push_back(NORMAL);
    scopes.push_back(FIGHT);
    description = "equip an item";
    dev_command = false;
    command_time = 0.13;
}

void C_equip::commence(std::vector<std::string> splitted_input) {
    int item_index = session.player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    Item* item = session.player->getItemAtIndex(item_index);
    if (item->tagsContain(ATTACKITEMTAG)) {
        session.player->updateTimeInFight(1.5);
        session.player->equipItem(item);
    } else {
        cantAttackWithItemDialog();
    }
}

/* ===================================== */

C_attack::C_attack() {
    command = "attack";
    args = vector<string>();
    scopes.push_back(FIGHT);
    description = "attack with equipped weapon";
    dev_command = false;
    command_time = 0.05;
}

void C_attack::commence(std::vector<std::string> splitted_input) {
    session.attacked = true;
    session.player->updateTimeInFight(session.enemy_fighting->getSpeed());
    session.updateWorldTimer(0.05);
    int damage = session.player->attack(session.enemy_fighting->getName());
    session.enemy_fighting->getDamaged(damage);
}

/* ===================================== */

C_stock::C_stock() {
    command = "stock";
    args = vector<string>();
    scopes.push_back(SHOP);
    description = "check out store's stock";
    dev_command = false;
    command_time = 0.18;
}

void C_stock::commence(std::vector<std::string> splitted_input) {
    ShopBlock* shopblock = (ShopBlock*)session.getBlockAtPlayerLocation();
    shopblock->printStock();
}

// /* ===================================== */

C_buy::C_buy() {
    command = "buy";
    args = vector<string>({"item name"});
    scopes.push_back(SHOP);
    description = "buy an item";
    dev_command = false;
    command_time = 0.19;
}

void C_buy::commence(std::vector<std::string> splitted_input) {
    ShopBlock* shopblock = (ShopBlock*)session.getBlockAtPlayerLocation();
    int index = shopblock->indexItem(splitted_input[1]);
    if (index == NOTFOUND) {
        itemNotInStockDialog();
        return;
    }
    int price = shopblock->getItemPrice(index);
    if (price > session.player->getCoins()){
        notEnoughCoinsDialog();
        return;
    }
    session.player->deductCoins(price);
    Item* item = shopblock->buyItem(index);
    session.player->addItem(item);
}

// /* ===================================== */

// C_use::C_use() {
//     command = "use";
//     args = vector<string>({"item_name"});
//     scopes.push_back(ALL);
//     description = "use an item";
//     dev_command = false;
//     command_time = 0.15;
// }

// void C_use::commence(std::vector<std::string> splitted_input) {
    
// }