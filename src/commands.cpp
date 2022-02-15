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
}

void Command::commence(std::vector<std::string> splitted_input) {
    cout<< "base commence was called!" << endl;
}

/* ============= Commands ============== */

C_move::C_move() {
    command = "move";
    args = vector<string>({"direction"});
    scope.push_back(NORMAL);
    description = "use this command to move around the map";
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
    session.updateWorldTimer(session.getPlayerMoveTime());
    session.can_spawn_enemy = true;
    session.handleNewReachedBlock();
}


