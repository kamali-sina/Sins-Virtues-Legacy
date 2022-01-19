#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include <string>
#include <vector>
#include <iostream>

enum Scopes { 
    NORMAL,
    FIGHT,
    PROMPT,
    SHOP,
    BLACKSMITH
};

class Command {
    public:
    Command();
    virtual void commence(std::vector<std::string> splitted_input);

    private:
    std::string command;
    std::vector<std::string> args;
    std::vector<int> scope;
    std::string description;

};

#endif