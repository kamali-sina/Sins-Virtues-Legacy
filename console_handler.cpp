#include "console_handler.hpp"

using namespace std;

string HELP_OPTIONS[] =  {"-h", "--help"};
string TOTURIAL_OPTIONS[] =  {"-t", "--toturial"};
string NEWGAME = "-n";
string LOADGAME = "-l";

float _random() {
    int r = rand();
    return float(float(r) / float(RAND_MAX));
}

void _sleep(float time) {
    int milli = time * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

string lower(string input) {
    std::for_each(input.begin(), input.end(), [](char & c) {
        c = ::tolower(c);
    });
    return input;
}

vector<string> split_string(string input, char delim) {
    vector<string> output;
    string part;
    stringstream s(input);
    while (getline(s, part, delim)) { 
        output.push_back(part); 
    } 
    return output;
}

void _error(std::string msg) {
    cprint("ERROR: " + msg, RED);
}

int signal = 0;
void* wait_for_input(void* i) {
    getch();
    signal = 1;
    return NULL;
}

void slow(std::string text, float speed) {
    /*function which displays characters one at a time*/
    pthread_t thread;
    signal = 0;
    pthread_create(&thread, NULL, wait_for_input, NULL);
    for (int i = 0; i < text.length(); i++) {
        cout<<text[i];
        std::cout.setf( std::ios_base::unitbuf ); //flushes cout
        if (signal) {
            for (int j = i+1; j < text.length(); j++) {cout<<text[j];}
            return;
        }
        int r = rand();
        float x = 1 + ((float(float(r) / float(RAND_MAX)) - 0.5) * 0.5);
        int milli = (1/(speed * x)) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(milli));
    }
    pthread_cancel(thread);
    resetTermios();
    return;
}

void dialog(std::string name , std::string text, std::string color, float speed) {
    /* prints endl automatically! */
    cout<<colored(name, color)<<": ";
    std::cout.setf( std::ios_base::unitbuf ); //flushes cout
    slow(text, speed=speed);
    cout<<endl;
}

void notification(string msg) {
    slow(msg, 30);
    cout<<endl;
}

void toturial_if_needed(string option) {
    if (find(begin(TOTURIAL_OPTIONS), end(TOTURIAL_OPTIONS), option) != end(TOTURIAL_OPTIONS)) {
        cprint("\n=== welcome to Sins & Virtues! ===\n", BLUE);
        cout<<"This game is completely text based. There are no maps(yet), no hints, no eagle vision, no nothing."<<endl;
        cout<<"But that does not mean that you are completely blind! The protagonist constantly talks about his surroundings, everything he says is there for a reason, so don\'t skip all the dialogs!"<<endl;
        cprint("\n===HOW TO PLAY THE GAME===\n", GREEN);
        cout<<"Everytime you see a little \">\" on the screen it\'s your turn to play the game. You have a handful of commands that you can use in every situation that you can review by typing \"commands\"."<<endl;
        cout<<"Each of the commands that you can use do use some time, this becomes important specially in the fights where losing time could mean death."<<endl;
        cout<<"We suggest testing and exploring the commnads by yourself, but if you want more info on some commands you can:"<<endl;
        cout<<"\tGo to our github page and read the complete readme: https://github.com/PapaSinku/Sins-Virtues"<<endl;
        cprint("\n===Shops===\n", YELLOW);
        cout<<"There are some shops located in the game that you can use to sell your unwanted items and buy the things you want. The currencies in this game are \"coins\"."<<endl;
        cout<<"Not all shopkeepers are the same, some have higher prices, some buy your items at a higher price. explore and find the shopkeeper that suits you the best."<<endl;
        cprint("\n===Homes===\n", GREEN);
        cout<<"Homes can be used to rest the night and restore your hp. They also usualy contains a good item inside."<<endl;
        cout<<"But not all homes are empty. Enter with caution."<<endl;
        cprint("\n===Fights===\n", RED);
        cout<<"Fights in this game are text based also. The only command for attacking that you have is \"attack\" that uses the equipped item to attack the enemy."<<endl;
        cout<<"Each move you or your enemy make in a fight uses some time, the turns in the fights are calculated by using that time."<<endl;
        cout<<"Always make sure to have equipped your best weapon before exploring into the unknown. You never know when the next enemy is going to fight you and that extra \"equip\" might be what saves or kills you in the end."<<endl;
        cprint("\n===Castle===", MAGENTA);
        cout<<"To finish the game, you need to find the castle and explore it completely to the end. You have 2 options to find the castle:"<<endl;
        cout<<"\texplore blindly untill you come across the castle block"<<endl;
        cout<<"\tfind a compass. by using a compass the compass directs you to the castle location."<<endl;
        cprint("*Always go into the castle prepared. The enemies in there will kill you easily if you are not well prepared.*",RED);
        cout<<"\n\n===============\nHappy Exploring, goodnight!"<<endl;
        exit(0);
    }
}

void help_if_needed(string option) {
    if (find(begin(HELP_OPTIONS), end(HELP_OPTIONS), option) != end(HELP_OPTIONS)) {
        cout<<"Usage: ./VnS.out <options>\n"<<endl;
        cprint("=== welcome to Sins & Virtues! ===\n", BLUE);
        cout<<"use the following options to play the game:\n"<<endl;
        cout<<"  "<<colored(NEWGAME,YELLOW)<<": for starting a new game. \n    can be followed by the path to save the game. saves in the current directory as default\n"<<endl;
        // TODO: cout<<"  "<<colored(,YELLOW)<<": for resuming from a save file.\n    must be followed by the path to the save directory"<<endl;
        cout<<"  "<<colored(LOADGAME,YELLOW)<<": does not do anything currently.\n"<<endl;
        cout<<"  "<<colored(TOTURIAL_OPTIONS[0],YELLOW)<<": for learning the game. \n"<<endl;
        cout<<"  "<<colored(HELP_OPTIONS[0],YELLOW)<<": for seeing the page you are reading now. \n"<<endl;
    }
}