#include "game.hpp"

using namespace std;

typedef void (Game::*handler)(std::vector<std::string>);

std::map<std::string, handler> handlers;

vector<string> NORMAL_COMMANDS({"move", "inventory", "use", "info", "commands", "print_map", "equip"});
vector<string> FIGHT_COMMANDS({"inventory", "info", "use", "attack", "commands", "equip"});
vector<string> PROMPT_COMMANDS({"yes", "no", "y", "n"});
vector<string> SHOP_COMMANDS({"inventory", "info", "commands", "stock", "buy", "sell", "exit"});

void Game::init_handlers(){
    if (handlers["move"] == NULL){
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

Game::Game(bool newgame, string path){
    srand((unsigned int)time(NULL));
    init_handlers();
}

Game::Game(){
    return;
}

void Game::run(){
    while (true){
        string input;
        cout<<"> ";
        getline(cin, input);
        input = lower(input);
        vector<string> splitted_input = split_string(input, ' ');
        process_input(splitted_input);
    }
}

bool mini_valid(vector<string> command_set , string command){
    if (find(command_set.begin(), command_set.end(), command) != command_set.end()){
        return true;
    }
    return false;
}

bool Game::is_command_valid(string command){
    switch(state){
        case NORMAL:
            return mini_valid(NORMAL_COMMANDS, command);
        case FIGHT:
            return mini_valid(FIGHT_COMMANDS, command);
        case PROMPT:
            return mini_valid(PROMPT_COMMANDS, command);
        case SHOP:
            return mini_valid(SHOP_COMMANDS, command);
        default:
            _error("unknown error happened!");
            exit(0);
    }
    
}

void Game::process_input(vector<string> splitted_input){
    if (splitted_input.size() == 0){
        return;
    }
    if (is_command_valid(splitted_input[0]) && handlers[splitted_input[0]] != NULL){
        (*this.*handlers[splitted_input[0]])(splitted_input);
    }else{
        _error("command not found!");
    }
}

void Game::move(std::vector<std::string> splitted_input){
    cout<<"moving..."<<endl;
}

void Game::inventory(std::vector<std::string> splitted_input){
    cout<<"base inventory..."<<endl;
}

void Game::use(std::vector<std::string> splitted_input){
    cout<<"base use..."<<endl;
}

void Game::info(std::vector<std::string> splitted_input){
    cout<<"base info..."<<endl;
}

void Game::commands(std::vector<std::string> splitted_input){
    cout<<"base commands..."<<endl;
}

void Game::print_map(std::vector<std::string> splitted_input){
    cout<<"base print_map..."<<endl;
}

void Game::equip(std::vector<std::string> splitted_input){
    cout<<"base equip..."<<endl;
}

void Game::attack(std::vector<std::string> splitted_input){
    cout<<"base attack..."<<endl;
}

void Game::prompt_handler(std::vector<std::string> splitted_input){
    cout<<"base prompt_handler..."<<endl;
}

void Game::stock(std::vector<std::string> splitted_input){
    cout<<"base stock..."<<endl;
}

void Game::buy(std::vector<std::string> splitted_input){
    cout<<"base buy..."<<endl;
}

void Game::sell(std::vector<std::string> splitted_input){
    cout<<"base sell..."<<endl;
}

void Game::exit_to_world(std::vector<std::string> splitted_input){
    cout<<"base exit_to_world..."<<endl;
}