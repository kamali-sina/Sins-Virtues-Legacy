#include <iostream>
#include <vector>
#include <iomanip>
#include "console_handler.hpp"

using namespace std;

int main (int argc , char *argv[]){
    if (argc < 2){
        _error ("no arguments were provided.\n\nif you need help use -h or --help");
        return 0;
    }
    toturial_if_needed(argv[1]);
    help_if_needed(argv[1]);
    return 1;
}