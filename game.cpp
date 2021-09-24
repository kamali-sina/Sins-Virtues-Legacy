#include "game.hpp"

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

    }
}

Game::Game(bool newgame, string path, int _seed) {
    srand((unsigned int)time(NULL));
    init_handlers();
    save_path = path;
    if (newgame) {
        seed = _seed;
        if (seed == NOTFOUND)
            initSeed();
        map = new Map(seed);
        player = new Player();
        save();
        introCutscene();
    } else {
        load();
        loadCutscene();
    }
}

Game::Game() {
    return;
}

void Game::initSeed() {
    for (int i = 0 ; i < 69 ; i++) 
        seed = rand();
    srand(seed);
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

void Game::updateTimeOfDay() {
    int time;
    if (world_timer < 14) {
        time = 0;
    } else if (world_timer < 16) {
        time = 1;
    } else {
        time = 2;
    }
    if (time != time_of_day) {
        newTimeOfDayDialog(time);
    }
    time_of_day = time;
}

void Game::getPlayerInput(std::string color) {
    updateCommandSet();
    updateTimeOfDay();
    string input;
    cout<<endl;
    cout<<colored("> ", color);
    getline(cin, input);
    cout<<endl;
    input = lower(input);
    vector<string> splitted_input = split_string(input, ' ');
    validate_input(splitted_input);
    spawnNightTimeEnemey();
    can_spawn_enemy = false;
}

void Game::run() {
    updateCommandSet();
    while (true) {
        getPlayerInput(NOCOLOR);
    }
}

Block* Game::getBlockAtPlayerLocation() {
    return map->getBlockAtLocation(player->getLocation());
}

Player* Game::getPlayer() {
    return player;
}

Map* Game::getMap() {
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
    map->setBlockAtLocation(player->getLocation(), new NormalBlock(true));
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

void Game::spawnNightTimeEnemey() {
    if (time_of_day == NIGHT && state == NORMAL && can_spawn_enemy) {
        if (_random() < NIGHT_ENEMY_CHANCE) {
            Enemy* enemy = getRandomEnemy();
            cout<<endl;
            encounteredEnemyAtNightDialog(enemy->getName());
            fightEnemy(enemy);
        }
    }
}

float Game::getPlayerMoveTime() {
    float total_weight = player->getTotalWeight();
    float move_time = BASE_BLOCK_MOVE_TIME 
                + max((float)0, total_weight - ITEM_WEIGHT_SOFT_THRESHHOLD) * EXTRA_TIME_PER_KG;
    return move_time;
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
    if (!map->isLocationValid(new_location)){
        outOfBoundsDialog();
        return;
    }
    player->setLocation(new_location);
    updateWorldTimer(getPlayerMoveTime());
    can_spawn_enemy = true;
    handleNewReachedBlock();
}

void Game::handleNewReachedBlock() {
    Block* current_block = getBlockAtPlayerLocation();
    newBlockReachedDialog(current_block->getName(), current_block->getColor(), current_block->getInfo());
    map->printAdjacentDialogs(player->getLocation());
    if (current_block->getHasPrompt()){
        showPrompt(current_block->getPrompt(), current_block->getName(), current_block->getColor());
        bool ans = setupPrompt("", false);
        prompt_handler(ans);
    }
}

bool Game::isBlockClosed(std::string block_name) {
    if (time_of_day == NIGHT) {
        blockIsClosedDialog(block_name);
        return true;
    }
    return false;
}

void Game::enterBlacksmith() {
    if (isBlockClosed("blacksmith")) return;
    cout<< colored("--Entered Blacksmith--\n", BLUE) << endl;
    welcomeToBlacksmithDialog();
    state = BLACKSMITH;
    updateCommandSet();
    while (state == BLACKSMITH){
        getPlayerInput(BLUE);
    }
    updateCommandSet();
}

void Game::enterShop() {
    if (isBlockClosed("shop")) return;
    cout<< colored("--Entered Shop--\n",YELLOW) << endl;
    welcomeToShopDialog();
    state = SHOP;
    updateCommandSet();
    while (state == SHOP){
        getPlayerInput(YELLOW);
    }
    updateCommandSet();
}

void Game::printFightStatus() {
    cout<< colored("Your hp",GREEN)  << ": " << player->getHP() << endl;
    cout<< colored("Enemy's hp",RED) << ": " << enemy_fighting->getHP() << endl << endl;
}

void Game::playKillCutscene() {
    notification("the " +  enemy_fighting->getName() +" is dead.");
    dialog("You", enemy_fighting->getKillDialog(), YELLOW, 28);
    player->addCoins(enemy_fighting->getBounty());
}

void Game::fightBoss(Boss* boss) {
    echoBossIntroDialog(boss->getName(), boss->getIntroDialog());
    fightEnemy(boss);
}

void Game::fightEnemy(Enemy* enemy) {
    enemy_fighting = enemy;
    enemy_fighting->updateScaling(days_passed);
    cout<< colored("\n--Entered Battle--\n", RED) << endl;
    notification(enemy_fighting->getInfo());
    cout<< endl;
    int save_state = state;
    state = FIGHT;
    player->resetTimeInFight(enemy_fighting->getSpeed());
    enemy_fighting->resetTimeInFight(player->getSpeed());
    bool attacked = false;
    while (true) {
        if (enemy_fighting->getTimeInFight() < player->getTimeInFight()) {
            enemy_fighting->attack(player);
        } else {
            if (attacked) {
                attacked = false;
                //TODO: update status effects
            }
            printFightStatus();
            // self.player.print_affected_effects()
            getPlayerInput(RED);
        }

        if (enemy_fighting->isDead()) {
            playKillCutscene();
            break;
        }
    }
    // self.player.reset_status_effects()
    state = save_state;
}

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
    float t = (world_timer + 5.0);
    while (t > 24) t -= 24;
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
    can_spawn_enemy = true;
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
        UtilityItem* utility_item = (UtilityItem*) item;
        utility_item->use_item(item_index);
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
    cout<<"========== Day " + to_string(days_passed) + " ==========" <<endl<<endl;
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
    map->printPartialMap(2, player->getLocation());
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
    // TODO: update this if needed : self.attacked = True
    player->updateTimeInFight(enemy_fighting->getSpeed());
    updateWorldTimer(0.05);
    int damage = player->attack(enemy_fighting->getName());
    enemy_fighting->getDamaged(damage);
}

void Game::prompt_handler(bool ans) {
    getBlockAtPlayerLocation()->run_handler(ans);
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

bool Game::setupPrompt(std::string prompt, bool show_prompt) {
    if (show_prompt)
        notification(prompt + "(y, n)");
    string input;
    while (1){
        cout<<colored("> ", WHITE);
        getline(cin, input);
        cout<<endl;
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        input = splitted_input[0];
        if (input == "n" || input == "no") return false;
        else if (input == "y" || input == "yes") return true;
        _error("answer with y or n");
        cout<<endl;
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
    bool ans = setupPrompt("Sell " + splitted_input[1] + " for " + colored(to_string(sell_price), YELLOW) + " coins?");
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
    map->printFullMap();
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
                    + colored(item->getName(), RED) 
                    + " to level " 
                    + colored(to_string(level + 1), BOLDYELLOW) 
                    + " costs " 
                    + colored(to_string(price), YELLOW) + " scraps, upgrade?");
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
    bool ans = setupPrompt("scrap " + colored(attackitem->getName(), RED) 
                            + " for " + colored(to_string(price), BLACK) + " scraps?");
    if (ans) {
        player->scrapItem(item_index);
        postScrapDialog(attackitem->getName(), price);
        updateWorldTimer(0.6);
    }
}

void Game::save() {
    string save_file_path = save_path + SAVEFILENAME;
    ofstream file_obj;
    file_obj.open(save_file_path);
    file_obj << days_passed << endl;
    file_obj << seed << endl;
    player->save(save_path);
    map->save(save_path);
    file_obj.close();
}

void Game::load() {
    string save_file_path = save_path + SAVEFILENAME;
    ifstream file_obj;
    file_obj.open(save_file_path, ios::in);
    file_obj >> days_passed;
    file_obj >> seed;
    file_obj.close();
    Map* loaded_map = new Map();
    loaded_map->load(save_path);
    map = loaded_map;
    Player* loaded_player = new Player();
    loaded_player->load(save_path);
    player = loaded_player;
}