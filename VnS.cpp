#include "VnS.hpp"
#include "block.hpp"
#include "utilities.hpp"

using namespace std;

Game session;

int main (int argc , char *argv[]) {
    srand((unsigned int)time(NULL));
    if (argc < 2){
        _error ("no arguments were provided.\n\nif you need help use -h or --help");
        return 0;
    }
    string option = argv[1];
    string input_path;
    if (argc > 2) {
        input_path = argv[2];
    } else {
        input_path = DEFAULTSAVEPATH;
    }
    bool newgame = false;
    string save_path = ""; 
    toturialIfNeeded(option);
    helpIfNeeded(option);
    if ( option == NEWGAME) {
        save_path = handleNewGame(input_path);
        newgame = true;
    } else if (option == LOADGAME) {
        save_path = handleLoadGame(input_path);
        newgame = false;
    } else { 
        _error("Invalid option was provided, use --help for more info!");
    }
    session = Game(newgame, save_path);
    session.run();
    // session.getPlayer()->printInventory();
    return 1;
}