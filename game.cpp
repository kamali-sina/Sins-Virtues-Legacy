#include "game.hpp"
#include "handlers.hpp"

using namespace std;

typedef void (Game::*handler)(std::vector<std::string>);

std::map<std::string, handler> handlers;

vector<string> NORMAL_COMMANDS({"move", "inventory", "use", "info", "commands", "print_map", "equip", "dev_map"});
vector<int> NORMAL_COMMANDS_COUNT({2, 1, 2, 1, 1, 1, 2, 1});
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
        handlers["dev_map"] = &Game::dev_map;

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
        validate_input(splitted_input);
    }
}

Block* Game::getBlockAtPlayerLocation() {
    return map.getBlockAtLocation(player->getLocation());
}

Player* Game::getPlayer() {
    return player;
}

Map Game::getMap() {
    return map;
}

void Game::digHere(int inventory_index) {
    Block* block = getBlockAtPlayerLocation();
    if (block->getID() != DIGABLEBLOCK) {
        cantDigHereDialog();
        return;
    }
    DigableBlock* digableBlock = (DigableBlock*)block;
    player->useItem(inventory_index);
    if (digableBlock->getContainsItem()) {
        digableBlock->setContainsItem(false);
        Item* item = digableBlock->getItemInside();
        foundItemDialog(item->getName());
        player->addItem(item);
    } else {
        didntFindItemDialog();
    }
    map.setBlockAtLocation(player->getLocation(), new NormalBlock(true));
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

void Game::validate_input(vector<string> splitted_input) {
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
    map.printAdjacentDialogs(player->getLocation());
    if (current_block->getHasPrompt()){
        showPrompt(current_block->getPrompt(), current_block->getName(), current_block->getColor());
        state = PROMPT;
    }
}

// TODO:
// def fight_enemy(self, enemy):
//         print(colored('\n--Entered Battle--\n','red'))
//         notification('enemy info:\n' + str(enemy), speed=18)
//         print()
//         save_state = self.state
//         self.state = 'fight'
//         self.set_command_set()
//         self.enemy = enemy
//         self.my_time = float(enemy.speed)
//         self.enemy_time = float(self.player.equipped.speed)
//         self.attacked = False
//         while(True):
//             if (self.enemy_time < self.my_time):
//                 #Enemy's turn to attack!
//                 notification(self.enemy.attack(self.player), speed=26)
//                 self.enemy_time += self.player.equipped.speed
//             else:
//                 #our turn to attack
//                 if (self.attacked):
//                     self.attacked = False
//                     self.player.update_status_effects()
//                 print(colored("Your hp",'green') + f': {self.player.hp}')
//                 print(colored("Enemy's hp",'red') + f': {self.enemy.hp}\n')
//                 self.player.print_affected_effects()
//                 input_str = input(colored("> ",'red')).strip().lower()
//                 self.process_input(input_str)
//             if(self.enemy.hp <= 0):
//                 notification(f'the {colored(self.enemy.name, "red")} is dead.', speed=20)
//                 print()
//                 dialog("You", self.enemy.get_kill_dialog(), "yellow", speed=18)
//                 self.player.coin += self.enemy.bounty
//                 break
//         self.player.reset_status_effects()
//         self.state = save_state

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
    map.printPartialMap(2, player->getLocation());
}

void Game::equip(std::vector<std::string> splitted_input) {
    cout<<"base equip..."<<endl;
}

void Game::attack(std::vector<std::string> splitted_input) {
    cout<<"base attack..."<<endl;
}

void Game::prompt_handler(std::vector<std::string> splitted_input) {
    bool ans = false;
    if (splitted_input[0] == "yes" || splitted_input[0] == "y"){
        ans = true;
    }
    runBlockHandler(ans, *this);
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

void Game::dev_map(std::vector<std::string> splitted_input) {
    map.printFullMap();
}