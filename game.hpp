#ifndef _GAME_HPP
#define _GAME_HPP

#include <vector>
#include <iostream>
#include <string>
#include "console_handler.hpp"

#define NORMAL 0
#define FIGHT 1
#define PROMPT 2
#define SHOP 3

extern std::string NORMAL_COMMANDS[];
extern std::string NORMAL_COMMANDS_HANDLER[];
extern std::string FIGHT_COMMANDS[];
extern std::string FIGHT_COMMANDS_HANDLER[];
extern std::string PROMPT_COMMANDS[];
extern std::string PROMPT_COMMANDS_HANDLER[];
extern std::string SHOP_COMMANDS[];
extern std::string SHOP_COMMANDS_HANDLER[];

class Game{
    public:
    Game(bool newgame, std::string path);
    Game();
    void run();
    void move(std::vector<std::string> splitted_input);




    float player_time = 0.0;
    float enemy_time = 0.0;
    float world_time = 0.0;
    int state = NORMAL; 
    //TODO: add player and map
    private:
    void process_input(std::vector<std::string> splitted_input);
    int idiot_counter = 0;
};

#endif