#include "game.hpp"
#include "handlers.hpp"

using namespace std;

typedef void (Game::*handler)(std::vector<std::string>);

std::map<std::string, handler> handlers;

vector<string> NORMAL_COMMANDS({"move", "inventory", "use", "info", "commands", "print_map", "equip"});
vector<int> NORMAL_COMMANDS_COUNT({2, 1, 2, 1, 1, 1, 2});
vector<string> FIGHT_COMMANDS({"inventory", "info", "use", "attack", "commands", "equip"});
vector<int> FIGHT_COMMANDS_COUNT({1, 1, 2, 1, 1, 2});
vector<string> PROMPT_COMMANDS({"yes", "no", "y", "n"});
vector<int> PROMPT_COMMANDS_COUNT({1, 1, 1, 1});
vector<string> SHOP_COMMANDS({"inventory", "info", "commands", "stock", "buy", "sell", "exit"});
vector<int> SHOP_COMMANDS_COUNT({1, 1, 1, 1, 2, 2, 1});

void Game::init_handlers() {
    if (handlers["move"] == NULL) {
        handlers["move"] = &Game::move;
        handlers["inventory"] = &Game::inventory;
        handlers["use"] = &Game::use;
        handlers["info"] = &Game::info;
        handlers["commands"] = &Game::commands;
        handlers["print_map"] = &Game::print_map;
        handlers["equip"] = &Game::equip;
        handlers["attack"] = &Game::attack;
        handlers["stock"] = &Game::stock;
        handlers["buy"] = &Game::buy;
        handlers["sell"] = &Game::sell;
        handlers["exit"] = &Game::exit_to_world;

        handlers["y"] = &Game::prompt_handler;
        handlers["n"] = &Game::prompt_handler;
        handlers["yes"] = &Game::prompt_handler;
        handlers["no"] = &Game::prompt_handler;
    }
}

Game::Game(bool newgame, string path) {
    srand((unsigned int)time(NULL));
    init_handlers();
}

Game::Game() {
    return;
}

void Game::run() {
    while (true) {
        string input;
        cout<<"> ";
        getline(cin, input);
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        process_input(splitted_input);
    }
}

Block* Game::getBlockAtPlayerLocation() {
    return map.getBlockAtLocation(player->getLocation());
}

Player* Game::getPlayer() {
    return player;
}

bool mini_valid(vector<string> command_set, vector<int> command_count, string command, int count) {
    int index = find(command_set.begin(), command_set.end(), command) - command_set.begin();
    if (index != command_set.size()) {
        if (command_count[index] == count)
            return true;
    }
    return false;
}

template <typename T>
int index_item(std::vector<T> list, T to_be_found) {
   for (int i = 0 ; i < list.size() ; i++) {
       if (list[i] == to_be_found) return i;
   }
   return -1;
}

bool Game::is_command_valid(string command, int count) {
    switch(state) {
        case NORMAL:
            return mini_valid(NORMAL_COMMANDS, NORMAL_COMMANDS_COUNT,command, count);
        case FIGHT:
            return mini_valid(FIGHT_COMMANDS, FIGHT_COMMANDS_COUNT,command, count);
        case PROMPT:
            return mini_valid(PROMPT_COMMANDS, PROMPT_COMMANDS_COUNT, command, count);
        case SHOP:
            return mini_valid(SHOP_COMMANDS, SHOP_COMMANDS_COUNT, command, count);
        default:
            _error("unknown error happened!");
            exit(0);
    }
    
}

void Game::process_input(vector<string> splitted_input) {
    if (splitted_input.size() == 0) {
        return;
    }
    if (is_command_valid(splitted_input[0], splitted_input.size()) && handlers[splitted_input[0]] != NULL) {
        (*this.*handlers[splitted_input[0]])(splitted_input);
    }else{
        _error("command is invalid!");
    }
}

void Game::move(std::vector<std::string> splitted_input) {
    vector<string> moveset({"north", "south", "east", "west", "up", "down", "left", "right"});
    vector<pair<int,int>> moveset_handler({pair<int,int>(1,0), pair<int,int>(-1,0), pair<int,int>(0,1), pair<int,int>(0,-1),
         pair<int,int>(1,0), pair<int,int>(-1,0), pair<int,int>(0,-1), pair<int,int>(0,1)});
    int index = index_item<string>(moveset, splitted_input[1]);
    if (index == -1){
        _error("command is invalid!");
        return;
    }
    pair<int,int> new_location(player->getLocation().first + moveset_handler[index].first,
        player->getLocation().second + moveset_handler[index].second);
    if (!map.isLocationValid(new_location)){
        outOfBoundsDialog();
        return;
    }
    player->setLocation(new_location);
    handleNewReachedBlock();
}

void Game::handleNewReachedBlock() {
    Block* current_block = getBlockAtPlayerLocation();
    newBlockReachedDialog(current_block->getName(), current_block->getInfo());
    // map.printAdjacentDialogs(player->getLocation());
    if (current_block->getHasPrompt()){
        showPrompt(current_block->getPrompt(), current_block->getName(), current_block->getColor());
        state = PROMPT;
    }
}

/*
current_block = self.map.get(self.player.location)
ConsoleHandler.new_block_reached_dialog(current_block)
self.print_adjacent_dialogs()
if (current_block.has_special_prompt):
    slow(current_block.get_prompt() + '\n')
    self.state = 'prompt'
*/

void Game::inventory(std::vector<std::string> splitted_input) {
    cout<<"base inventory..."<<endl;
}

void Game::use(std::vector<std::string> splitted_input) {
    cout<<"base use..."<<endl;
}

void Game::info(std::vector<std::string> splitted_input) {
    cout<<"player location: "<< player->getLocation().first << "," << player->getLocation().second<<endl;
}

void Game::commands(std::vector<std::string> splitted_input) {
    cout<<"base commands..."<<endl;
}

void Game::print_map(std::vector<std::string> splitted_input) {
    map.printFullMap();
}

void Game::equip(std::vector<std::string> splitted_input) {
    cout<<"base equip..."<<endl;
}

void Game::attack(std::vector<std::string> splitted_input) {
    cout<<"base attack..."<<endl;
}

void Game::prompt_handler(std::vector<std::string> splitted_input) {
    cout<<"base prompt_handler..."<<endl;
    state = NORMAL;
}

void Game::stock(std::vector<std::string> splitted_input) {
    cout<<"base stock..."<<endl;
}

void Game::buy(std::vector<std::string> splitted_input) {
    cout<<"base buy..."<<endl;
}

void Game::sell(std::vector<std::string> splitted_input) {
    cout<<"base sell..."<<endl;
}

void Game::exit_to_world(std::vector<std::string> splitted_input) {
    cout<<"base exit_to_world..."<<endl;
}