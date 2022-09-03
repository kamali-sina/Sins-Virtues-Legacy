#include "game.hpp"

using namespace std;

typedef void (Game::*handler)(std::vector<std::string>);

void Game::initHandlers() {
    all_commands.push_back(new C_move());
    all_commands.push_back(new C_inventory());
    all_commands.push_back(new C_use());
    all_commands.push_back(new C_info());
    all_commands.push_back(new C_commands());
    all_commands.push_back(new C_dev_print_map());
    all_commands.push_back(new C_dev_map());
    all_commands.push_back(new C_equip());
    all_commands.push_back(new C_attack());
    all_commands.push_back(new C_stock());
    all_commands.push_back(new C_buy());
    all_commands.push_back(new C_sell());
    all_commands.push_back(new C_exit());
    all_commands.push_back(new C_upgrade());
    all_commands.push_back(new C_scrap());
}

Game::Game(bool newgame, string path, int _seed, bool _dev_mode) {
    srand((unsigned int)time(NULL));
    initHandlers();
    save_path = path;
    dev_mode = _dev_mode;
    if (newgame) {
        seed = _seed;
        if (seed == NOTFOUND)
            initSeed();
        map = new Map(seed);
        player = new Player(dev_mode);
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
    updateTimeOfDay();
    string input;
    cout<<endl;
    cout<<colored("> ", color);
    getline(cin, input);
    cout<<endl;
    input = lower(input);
    vector<string> splitted_input = split_string(input, ' ');
    validateInput(splitted_input);
    spawnNightTimeEnemey();
    can_spawn_enemy = false;
}

void Game::run() {
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

bool is_dev_command(string command) {
    int pos = command.find(DEV_PREFIX);
    if (pos < 0) {
        return false;
    }
    return true;
}

template <typename T>
int index_item(std::vector<T> list, T to_be_found) {
   for (int i = 0 ; i < list.size() ; i++) {
       if (list[i] == to_be_found) return i;
   }
   return NOTFOUND;
}

bool Game::isCommandAvailable(Command* command) {
    if (command->isInScope(state)) {
        if (command->isDevOnly() && !dev_mode) {
            return false;
        }
        return true;
    }
    return false;
}

bool isCommandInputCorrect(Command* command, int input_size) {
    return command->getArgs().size() == input_size - 1;
}

Command* Game::findCommand(string command_name) {
    for (auto& command : all_commands) {
        if (command->getCommand() == command_name) return command;
    }
    return NULL;
}

void Game::validateInput(vector<string> splitted_input) {
    if (splitted_input.size() == 0) {
        return;
    }
    Command* command = findCommand(splitted_input[0]);
    if (command == NULL) {
        _error("command is invalid!");
        return;
    }
    if (!isCommandInputCorrect(command, splitted_input.size())) {
        _error("command is invalid!");
        return;
    }
    if (isCommandAvailable(command)) {
        command->commence(splitted_input);
        updateWorldTimer(command->getCommandTime());
    }else{
        _error("command is unavailable!");
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

void Game::handleNewReachedBlock() {
    Block* current_block = getBlockAtPlayerLocation();
    newBlockReachedDialog(current_block->getName(), current_block->getColor(), current_block->getInfo());
    map->printAdjacentDialogs(player->getLocation());
    if (current_block->tagsContain(SPECIALTAG)) {
        current_block->setHasAdjacentDialog(false);
        Notepad* notepad = (Notepad*)player->getItemAtIndex(player->indexItem(NOTEPAD));
        notepad->addEntry(current_block->getName(), current_block->getColor(), player->getLocation());
    }
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
    while (state == BLACKSMITH){
        getPlayerInput(BLUE);
    }
}

void Game::enterShop() {
    if (isBlockClosed("shop")) return;
    cout<< colored("--Entered Shop--\n",YELLOW) << endl;
    welcomeToShopDialog();
    state = SHOP;
    while (state == SHOP){
        getPlayerInput(YELLOW);
    }
}

void Game::printFightStatus() {
    cout<< colored("Your hp",GREEN)  << ": " << player->getHP() << endl;
    cout<< colored("Enemy's hp",RED) << ": " << enemy_fighting->getHP() << endl << endl;
    if (player->getStatusEffectCount() > 0) {
        string _count = colored(to_string(player->getStatusEffectCount()), BOLDMAGENTA);
        cout<< "you are affected by " << _count << " status effects!" << endl;
    }
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
    attacked = false;
    while (true) {
        if (enemy_fighting->getTimeInFight() < player->getTimeInFight()) {
            enemy_fighting->attack(player);
        } else {
            if (attacked) {
                attacked = false;
                player->applyStatusEffects();
            }
            printFightStatus();
            getPlayerInput(RED);
        }

        if (enemy_fighting->isDead()) {
            playKillCutscene();
            break;
        }
    }
    player->resetStatusEffectsList();
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

void Game::prompt_handler(bool ans) {
    getBlockAtPlayerLocation()->run_handler(ans);
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