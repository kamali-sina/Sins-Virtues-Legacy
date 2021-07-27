#ifndef _GAME_HPP
#define _GAME_HPP

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include "console_handler.hpp"
#include "map.hpp"
#include "player.hpp"

#define NORMAL 0
#define FIGHT 1
#define PROMPT 2
#define SHOP 3

extern std::vector<std::string> NORMAL_COMMANDS;
extern std::vector<std::string> FIGHT_COMMANDS;
extern std::vector<std::string> PROMPT_COMMANDS;
extern std::vector<std::string> SHOP_COMMANDS;

class Game{
    public:
    Game(bool newgame, std::string path);
    Game();
    Block* getBlockAtPlayerLocation();
    Player* getPlayer();
    Map getMap();
    void run();

    // command handlers
    void move(std::vector<std::string> splitted_input);
    void inventory(std::vector<std::string> splitted_input);
    void use(std::vector<std::string> splitted_input);
    void info(std::vector<std::string> splitted_input);
    void commands(std::vector<std::string> splitted_input);
    void print_map(std::vector<std::string> splitted_input);
    void equip(std::vector<std::string> splitted_input);
    void attack(std::vector<std::string> splitted_input);
    void prompt_handler(std::vector<std::string> splitted_input);
    void stock(std::vector<std::string> splitted_input);
    void buy(std::vector<std::string> splitted_input);
    void sell(std::vector<std::string> splitted_input);
    void exit_to_world(std::vector<std::string> splitted_input);

    void digHere(int inventory_index);
    //TODO: 
    void enterBlacksmith();
    void enterShop();
    void fightEnemy(Enemy* enemy);

    float player_time = 0.0;
    float enemy_time = 0.0;
    float world_time = 0.0;
    int state = NORMAL; 
    
    private:
    Map map;
    Player *player = new Player();
    int idiot_counter = 0;

    void validate_input(std::vector<std::string> splitted_input);
    void init_handlers();
    bool is_command_valid(std::string command, int count);
    void handleNewReachedBlock();
};

#endif