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
    scope.push_back(NORMAL);
    description = "base command that is going to be devrived!";
    dev_command = false;
    command_time = 0.0;
}

void Command::commence(std::vector<std::string> splitted_input) {
    cout<< "base commence was called!" << endl;
}

/* ============= Commands ============== */

C_move::C_move() {
    command = "move";
    args = vector<string>({"direction"});
    scope.push_back(NORMAL);
    description = "move around the map";
    dev_command = false;
}

void C_move::commence(std::vector<std::string> splitted_input) {
    vector<string> moveset({"north", "south", "east", "west", "up", "down", "left", "right"});
    vector<pair<int,int>> moveset_handler({pair<int,int>(1,0), pair<int,int>(-1,0), pair<int,int>(0,1), pair<int,int>(0,-1),
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
    // TODO: HANDLE IN GAME::: session.updateWorldTimer();
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
    scope.push_back(ALL);
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
    args = vector<string>({"item_name"});
    scope.push_back(ALL);
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
    command = "use";
    args = vector<string>();
    scope.push_back(ALL);
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

/* ==================TODO:=================== */

C_use::C_use() {
    command = "use";
    args = vector<string>({"item_name"});
    scope.push_back(ALL);
    description = "use an item";
    dev_command = false;
    command_time = 0.15;
}

void C_use::commence(std::vector<std::string> splitted_input) {
    
}

/* ===================================== */

C_use::C_use() {
    command = "use";
    args = vector<string>({"item_name"});
    scope.push_back(ALL);
    description = "use an item";
    dev_command = false;
    command_time = 0.15;
}

void C_use::commence(std::vector<std::string> splitted_input) {
    
}