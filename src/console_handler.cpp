#include "console_handler.hpp"

using namespace std;

string HELP_OPTIONS[] =  {"-h", "--help"};
string TOTURIAL_OPTIONS[] =  {"-t", "--toturial"};
struct stat info;

/* Returns: a random number between 0 and 1 */
float _random() {
    int r = rand();
    return float(float(r) / float(RAND_MAX));
}

void _sleep(float time) {
    int milli = time * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

string lower(string input) {
    for(auto& c : input) {
        c = tolower(c);
    }
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

int signalFlag = 0;
void* wait_for_input(void* i) {
    getch();
    signalFlag = 1;
    return NULL;
}

/*function which displays characters one at a time*/
void slow(std::string text, float speed) {
    pthread_t thread;
    initTermios(0);
    signalFlag = 0;
    pthread_create(&thread, NULL, wait_for_input, NULL);
    for (int i = 0; i < text.length(); i++) {
        if ((int)text[i] == STARTOFCOLORCODE) {
            while (text[i] != 'm') {
                cout<<text[i];
                i++;
            } 
        }
        cout<<text[i];
        std::cout.setf( std::ios_base::unitbuf ); //flushes cout
        if (signalFlag) {
            for (int j = i+1; j < text.length(); j++) {cout<<text[j];}
            restoreTermios();
            return;
        }
        int r = rand();
        float x = 1 + ((float(float(r) / float(RAND_MAX)) - 0.5) * 0.5);
        int milli = (1/(speed * x)) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(milli));
    }
    pthread_cancel(thread);
    restoreTermios();
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

void toturialIfNeeded(string option) {
    if (find(begin(TOTURIAL_OPTIONS), end(TOTURIAL_OPTIONS), option) != end(TOTURIAL_OPTIONS)) {
        cprint("\n=== welcome to Sins & Virtues! ===\n", BLUE);
        cout<<"To learn the game to the fullest, go read the Tutorial.md that is included in the folder of your game"<<endl;
        exit(0);
    }
}

void helpIfNeeded(string option) {
    if (find(begin(HELP_OPTIONS), end(HELP_OPTIONS), option) != end(HELP_OPTIONS)) {
        cout<<"\nUsage: ./VnS.out <options>\n"<<endl;
        cprint("=== welcome to Sins & Virtues! ===\n", BLUE);
        cout<<"use the following options to play the game:\n"<<endl;
        cout<<"  "<<colored(NEWGAME,YELLOW)<<": for starting a new game. \n    can be followed by the path to save the game. saves in the current directory as default\n"<<endl;
        cout<<"  "<<colored(LOADGAME,YELLOW)<<": for resuming from a save file.\n    must be followed by the path to the save directory"<<endl;
        cout<<"  "<<colored(SETSEED,YELLOW)<<": for setting a seed for the game, if not provided makes a random seed! \n"<<endl;
        cout<<"  "<<colored(TOTURIAL_OPTIONS[0],YELLOW)<<": for learning the game. \n"<<endl;
        cout<<"  "<<colored(HELP_OPTIONS[0],YELLOW)<<": for seeing the page you are reading now. \n"<<endl;
        exit(0);
    }
}

std::string handleNewGame(std::string path) {
    if (path[path.size() - 1] != '/') {
        path = path + "/";
    }
    string save_folder = path + SAVEFOLDRNAME + "/";
    if (stat( save_folder.c_str(), &info ) != 0) {
        cout<<"creating saves folder in " << path << endl;
        if (mkdir(save_folder.c_str(), 0777) == -1) {
            _error("Could not create save folder, does your path exist?");
            exit(0);
        }
        return save_folder;
    } else {
        cout<<"save folder already exists in path... override savefile?(y,n) ";
        string input;
        cin>>input;
        if (input == "y" || input == "yes") {
            cout<<"overriding savefile..." <<endl;
            return save_folder;
        } else {
            _error("aborting...");
            exit(0);
        }
    }
    return "";
}

std::string handleLoadGame(std::string path) {
    if (path[path.size() - 1] != '/') {
        path = path + "/";
    }
    string save_folder = path + SAVEFOLDRNAME + "/";
    if (stat( save_folder.c_str(), &info ) != 0) {
        _error("no save folder was detected in path!");
        exit(0);
    }
    cout<<"loading game from: " << path << endl;
    return save_folder;
}

void handleArgv(int argc , char *argv[], bool &newgame, std::string &save_path, int &seed, bool &dev_mode) {
    string input_path = DEFAULTSAVEPATH;
    for (int i = 1 ; i < argc ; i++) {
        string option = argv[i];
        toturialIfNeeded(option);
        helpIfNeeded(option);
        if (option == NEWGAME) {
            if (i + 1 < argc && argv[i+1][0] != '-') {
                input_path = argv[++i];
            }
            save_path = handleNewGame(input_path);
            newgame = true;
        } else if (option == LOADGAME) {
            if (i + 1 < argc && argv[i+1][0] != '-') {
                input_path = argv[++i];
            }
            save_path = handleLoadGame(input_path);
            newgame = false;
        } else if (option == SETSEED) {
            if (i + 1 >= argc || argv[i+1][0] == '-') {
                _error("options -s was used but no seed was given!");
                exit(1);
            }
            seed = stoi(argv[++i]);
            cprint("seed was set to " + to_string(seed), GREEN);
        } else if (option == DEVMODE) {
            dev_mode = true;
        } else {
            _error("Invalid option was provided, use --help for more info!");
            exit(1);
        }
    }
    if (save_path == "") {
        cprint("Starting new game...", BLUE);
        save_path = handleNewGame(input_path);
        newgame = true;
    }
}