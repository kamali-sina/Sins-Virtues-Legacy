#include "commands.hpp"
// #include "VnS.hpp"

using namespace std;

Command::Command() {
    command = "";
    args = vector<string>({"arg1", "arg2"});
    scope.push_back(NORMAL);
    description = "base command that is going to be devrived!";
}