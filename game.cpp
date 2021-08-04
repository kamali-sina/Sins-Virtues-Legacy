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
vector<string> BLACKSMITH_COMMANDS({"inventory", "info", "commands", "upgrade", "scrap", "exit"});
vector<int> BLACKSMITH_COMMANDS_COUNT({1, 1, 1, 2, 2, 1});

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
        handlers["upgrade"] = &Game::upgrade;
        handlers["scrap"] = &Game::scrap;

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

void Game::updateCommandSet() {
    switch(state) {
        case NORMAL:
            active_commandset = NORMAL_COMMANDS;
            active_commandset_count = NORMAL_COMMANDS_COUNT;
            return;
        case FIGHT:
            active_commandset = FIGHT_COMMANDS;
            active_commandset_count = FIGHT_COMMANDS_COUNT;
            return;
        case PROMPT:
            active_commandset = PROMPT_COMMANDS;
            active_commandset_count = PROMPT_COMMANDS_COUNT;
            return;
        case SHOP:
            active_commandset = SHOP_COMMANDS;
            active_commandset_count = SHOP_COMMANDS_COUNT;
            return;
        case BLACKSMITH:
            active_commandset = BLACKSMITH_COMMANDS;
            active_commandset_count = BLACKSMITH_COMMANDS_COUNT;
            return;
        default:
            _error("unknown error happened!");
            exit(0);
    }
}

void Game::run() {
    updateCommandSet();
    while (true) {
        string input;
        cout<<"> ";
        getline(cin, input);
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        validate_input(splitted_input);
        updateCommandSet();
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
    if (digableBlock->getContainsItem()) {
        digableBlock->setContainsItem(false);
        Item* item = digableBlock->getItemInside();
        player->addItem(item);
    } else {
        didntFindItemDialog();
    }
    player->useItem(inventory_index);
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
   return NOTFOUND;
}

bool Game::is_command_valid(string command, int count) {
    return mini_valid(active_commandset, active_commandset_count, command, count);
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
    if (index == NOTFOUND){
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
    updateWorldTimer(0.30);
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

void Game::enterBlacksmith() {
    cout<< colored("--Entered Blacksmith--\n", BLUE) << endl;
    welcomeToBlacksmithDialog();
    state = BLACKSMITH;
    updateCommandSet();
    while (state == BLACKSMITH){
        string input;
        cout<<colored("> ", BLUE);
        getline(cin, input);
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        validate_input(splitted_input);
        updateCommandSet();
    }
    updateCommandSet();
}

void Game::enterShop() {
    // TODO: if (self.is_block_closed('shop')): return
    cout<< colored("--Entered Shop--\n",YELLOW) << endl;
    welcomeToShopDialog();
    state = SHOP;
    updateCommandSet();
    while (state == SHOP){
        string input;
        cout<<colored("> ", YELLOW);
        getline(cin, input);
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        validate_input(splitted_input);
        updateCommandSet();
    }
    updateCommandSet();
}

void Game::fightEnemy(Enemy* enemy) {

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

void Game::updateWorldTimer(float value) {
    float multi = 1;
    world_timer += value * multi;
    if (world_timer > 24.0) {
        world_timer -= 24.0;
        days_passed += 1;
    }
}

void Game::resetWorldTimer() {
    world_timer = 0.0;
    days_passed += 1;
    time_of_day = DAY;
}

std::string Game::getClockTime() {
    float t = (int)(world_timer + 5.0) % 24;
    int h = t;
    int m = (t - h) * 60;
    string hour = to_string(h);
    string minutes = to_string(m);
    if (hour.length() < 2) hour = "0" + hour;
    if (minutes.length() < 2) minutes = "0" + minutes;
    return hour + ":" + minutes;
}

void Game::inventory(std::vector<std::string> splitted_input) {
    player->updateTimeInFight(0.5);
    updateWorldTimer(0.15);
    player->printInventory();
}

void Game::use(std::vector<std::string> splitted_input) {
    int item_index = player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    Item* item = player->getItemAtIndex(item_index);
    updateWorldTimer(0.1);
    if (item->tagsContain(UTILITYITEMTAG)) {
        runItemHandler(*this, item_index);
    } else if (item->tagsContain(HPITEMTAG)) {
        player->healWithItem(item_index);
    } else {
        cantUseItemDialog();
        return;
    }
    updateWorldTimer(0.2);
    player->updateTimeInFight(1.0);
}

void Game::info(std::vector<std::string> splitted_input) {
    updateWorldTimer(0.1);   
    player->printInfo();
    cout << "time: " << getClockTime() << endl;
    if (state == NORMAL){ 
        cout << "current block is " << colored(getBlockAtPlayerLocation()->getName(), MAGENTA) << endl;
    } else if (state == FIGHT) {
        // TODO: print(f'enemy has {colored(self.enemy.hp,"red")} hp left')
    } 
}

void Game::commands(std::vector<std::string> splitted_input) {
    cout<< "Available commands:" << endl;
    for (auto& command : active_commandset) {
        cout<< "                  " << colored("-", CYAN) << command << endl;
    }
}

void Game::print_map(std::vector<std::string> splitted_input) {
    map.printPartialMap(2, player->getLocation());
}

void Game::equip(std::vector<std::string> splitted_input) {
    int item_index = player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    updateWorldTimer(0.13);
    Item* item = player->getItemAtIndex(item_index);
    if (item->tagsContain(ATTACKITEMTAG)) {
        player->updateTimeInFight(1.5);
        player->equipItem(item);
    } else {
        cantAttackWithItemDialog();
    }
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
    ShopBlock* shopblock = (ShopBlock*)getBlockAtPlayerLocation();
    shopblock->printStock();
    updateWorldTimer(0.18);
}

void Game::buy(std::vector<std::string> splitted_input) {
    ShopBlock* shopblock = (ShopBlock*)getBlockAtPlayerLocation();
    int index = shopblock->indexItem(splitted_input[1]);
    if (index == NOTFOUND) {
        itemNotInStockDialog();
        return;
    }
    int price = shopblock->getItemPrice(index);
    if (price > player->getCoins()){
        notEnoughCoinsDialog();
        return;
    }
    player->deductCoins(price);
    Item* item = shopblock->buyItem(index);
    player->addItem(item);
}

bool Game::setupPrompt(std::string prompt) {
    notification(prompt + "(y, n)");
    string input;
    while (1){
        cout<<colored("> ", WHITE);
        cin>>input;
        if (input == "n" || input == "no") return false;
        else if (input == "y" || input == "yes") return true;
        _error("answer with y or n");
    }
}

void Game::sell(std::vector<std::string> splitted_input) {
    ShopBlock* shopBlock = (ShopBlock*)getBlockAtPlayerLocation();
    int item_index = player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    int sell_price = player->getPlayerSellPrice(item_index);
    bool ans = setupPrompt("Sell " + splitted_input[1] + " for " + to_string(sell_price) + " coins?");
    if (ans) {
        player->sellItem(item_index);
    } else {
        understandableHaveAGoodDialog();
    }
}

void Game::exit_to_world(std::vector<std::string> splitted_input) {
    cout<< "exiting..." << endl;
    updateWorldTimer(0.03);
    state = NORMAL;
}

void Game::dev_map(std::vector<std::string> splitted_input) {
    map.printFullMap();
}

void Game::upgrade(std::vector<std::string> splitted_input) {
    int item_index = player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    Item* item = player->getItemAtIndex(item_index);
    if (!item->tagsContain(ATTACKITEMTAG)) {
        itemNotUpgradbleDialog();
        return;
    }
    AttackItem* attackitem = (AttackItem*)item;
    int price = attackitem->getUpgradePrice();
    int level = attackitem->getLvl();
    if (level >= ATTACKITEMMAXLEVEL) {
        cantUpgradeMaxitemDialog();
        return;
    }
    bool ans = setupPrompt("upgrading the " 
                    + item->getName() 
                    + " to level " 
                    + to_string(level) 
                    + " costs " + to_string(price) + " scraps, upgrade?");
    if (ans) {
        if (player->getScraps() < price) {
            notEnoughScrapsDialog();
            return;
        }
        string response = attackitem->upgrade();
        player->deductScraps(price);
        updateWorldTimer(0.5);
        postUpgradeDialog(splitted_input[1], price, response);
    } else {
        dontWasteMyTimeDialog();
        return;
    }
}

void Game::scrap(std::vector<std::string> splitted_input) {
    int item_index = player->indexItem(splitted_input[1]);
    if (item_index == NOTFOUND) {
        dontHaveItemsDialog();
        return;
    }
    Item* item = player->getItemAtIndex(item_index);
    if (!item->tagsContain(ATTACKITEMTAG)) {
        itemNotScrappableDialog();
        return;
    }
    AttackItem* attackitem = (AttackItem*)item;
    updateWorldTimer(0.1);
    int price = attackitem->getScrapParts();
    bool ans = setupPrompt("scrap " + attackitem->getName() + " for " + to_string(price) + " scraps?");
    if (ans) {
        player->scrapItem(item_index);
        postScrapDialog(attackitem->getName(), price);
        updateWorldTimer(0.6);
    }
}