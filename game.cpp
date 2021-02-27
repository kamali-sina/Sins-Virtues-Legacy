#include "game.hpp"

using namespace std;

// string NORMAL_COMMANDS[] = {"move", "inventory", "use", "info", "commands", "map", "equip"};
// string NORMAL_COMMANDS_HANDLER[] = {self.move, self.inventory, self.use, self.info, self.commands, self.pmap, self.equip};

string FIGHT_COMMANDS[] = {"inventory", "info", "use", "attack", "commands", "equip"};
// string FIGHT_COMMANDS_HANDLER[] = {self.inventory, self.info, self.use, self.attack, self.commands, self.equip};
string PROMPT_COMMANDS[] = {"yes", "no", "y", "n"};
// string PROMPT_COMMANDS_HANDLER[] = {self.prompt_handler, self.prompt_handler, self.prompt_handler, self.prompt_handler};
string SHOP_COMMANDS[] = {"inventory", "info", "commands", "stock", "buy", "sell", "exit"};
// string SHOP_COMMANDS_HANDLER[] = {self.inventory, self.info, self.commands, self.stock, self.buy, self.sell, self.exit_shop};

Game::Game(bool newgame, string path){
    cout<<"state is "<<state<<endl;
}

Game::Game(){
    cout<<"normal constructor"<<endl;
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

void Game::move(std::vector<std::string> splitted_input){
    cout<<"moving..."<<endl;
}

void Game::process_input(vector<string> splitted_input){
    if (splitted_input[0] == "move"){
        this->move(splitted_input);
    }
}