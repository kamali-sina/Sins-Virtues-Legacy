#include "commands.hpp"
// #include "VnS.hpp"

using namespace std;

/* ============= Base Class ============== */

Command::Command() {
    command = "";
    args = vector<string>({"arg1", "arg2"});
    scope.push_back(NORMAL);
    description = "base command that is going to be devrived!";
    dev_command = false;
}

void Command::commence(std::vector<std::string> splitted_input) {
    cout<< "base commence was called!" << endl;
}

/* ============= Commands ============== */
