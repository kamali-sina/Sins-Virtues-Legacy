#include "VnS.hpp"
#include "block.hpp"
#include "utilities.hpp"

using namespace std;

Game session;

int main(int argc , char *argv[]) {
    srand((unsigned int)time(NULL));
    bool newgame = true;
    bool dev_mode = false;
    string save_path = ""; 
    int seed = NOTFOUND;
    handleArgv(argc, argv, OUTPARAM newgame, OUTPARAM save_path, OUTPARAM seed, OUTPARAM dev_mode);
    session = Game(newgame, save_path, seed, dev_mode);
    session.run();
    return 0;
}