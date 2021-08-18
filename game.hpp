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
#define BLACKSMITH 4

#define DAY 0
#define EVENING 1
#define NIGHT 2

#define NOTFOUND -1

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
    void dev_map(std::vector<std::string> splitted_input);
    void exit_to_world(std::vector<std::string> splitted_input);
    void upgrade(std::vector<std::string> splitted_input);
    void scrap(std::vector<std::string> splitted_input);

    void digHere(int inventory_index);
    void updateWorldTimer(float value);
    void resetWorldTimer();
    std::string getClockTime();
    void enterBlacksmith();
    void enterShop();
    bool isBlockClosed(std::string block_name);
    void printFightStatus();
    void getPlayerInput(std::string color);
    void playKillCutscene();
    //TODO: 
    void fightEnemy(Enemy* enemy);

    float player_time = 0.0;
    float enemy_time = 0.0;
    float world_timer = 0.0;
    int days_passed = 0;
    int time_of_day = DAY;
    int state = NORMAL; 
    
    
    private:
    Map map;
    Player *player = new Player();
    Enemy* enemy_fighting;
    int idiot_counter = 0;
    std::vector<std::string> active_commandset;
    std::vector<int> active_commandset_count;

    void validate_input(std::vector<std::string> splitted_input);
    void init_handlers();
    bool is_command_valid(std::string command, int count);
    void handleNewReachedBlock();
    void updateCommandSet();
    bool setupPrompt(std::string prompt);
};

/*
    TODO: save and load
    void save() {
        ofstream file_obj;
 
        // Opening file in append mode
        file_obj.open("save.txt", ios::app);
    
        // Object of class contestant to input data in file
    
        // Writing the object's data in file
        file_obj.write((char*)&*this, sizeof(*this));
    }

    void load() {
        ifstream file_obj;
 
        file_obj.open("save.txt", ios::in);
    
    
        // Reading from file into object "obj"
        file_obj.read((char*)&*this, sizeof(*this));
    
        print();
    }

    void print() {
        cout<<i<<endl;
    }

*/

#endif