#include "termcolor.hpp"

using namespace std;

void cprint(std::string string_to_print, std::string color){
    // Note that cprint prints an endl at the end of your string
    cout<<color<<string_to_print<<RESET<<endl;
}

std::string colored(std::string string_to_color, std::string color){
    string output = color + string_to_color + RESET;
    return output;
}