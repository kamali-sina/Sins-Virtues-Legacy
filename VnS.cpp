#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include "console_handler.hpp"

using namespace std;

int main (int argc , char *argv[]){
    srand((unsigned) time(0));
    if (argc < 2){
        _error ("no arguments were provided.\n\nif you need help use -h or --help");
        return 0;
    }
    toturial_if_needed(argv[1]);
    help_if_needed(argv[1]);
    dialog("You","yo I am a fucking piece of shot and I am tierd!", YELLOW, 13);
    string fuck;
    cin>>fuck;
    cout<<"fuck is: "<<fuck<<endl;
    return 1;
}