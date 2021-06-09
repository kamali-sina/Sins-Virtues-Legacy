#include "VnS.hpp"
#include "block.hpp"

using namespace std;

Game session = Game();

int main (int argc , char *argv[]){
    srand((unsigned int)time(NULL));
    if (argc < 2){
        _error ("no arguments were provided.\n\nif you need help use -h or --help");
        return 0;
    }
    toturial_if_needed(argv[1]);
    help_if_needed(argv[1]);
    session = Game(true, "");
    session.run();
    return 1;
}