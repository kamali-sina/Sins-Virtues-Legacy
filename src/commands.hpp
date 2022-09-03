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
    BLACKSMITH,
    ALL
};

class Command {
    public:
    Command();
    bool isInScope(int givenScope);
    bool isDevOnly();
    virtual void commence(std::vector<std::string> splitted_input);
    virtual float getCommandTime() { return command_time; }
    virtual std::string getCommand() {return command; }
    std::string getDescription() { return description; }
    std::vector<std::string> getArgs() { return args; }

    protected:
    std::string command;
    std::vector<std::string> args;
    std::vector<int> scopes;
    std::string description;
    float command_time = 0;
    bool dev_command = false;

};

class C_move : public Command {
    public:
    C_move();
    void commence(std::vector<std::string> splitted_input);
    float getCommandTime();
};

class C_inventory : public Command {
    public:
    C_inventory();
    void commence(std::vector<std::string> splitted_input);
};

class C_use : public Command {
    public:
    C_use();
    void commence(std::vector<std::string> splitted_input);
};

class C_info : public Command {
    public:
    C_info();
    void commence(std::vector<std::string> splitted_input);
};

class C_commands : public Command {
    public:
    C_commands();
    void commence(std::vector<std::string> splitted_input);
};

class C_dev_print_map : public Command {
    public:
    C_dev_print_map();
    void commence(std::vector<std::string> splitted_input);
};

class C_dev_map : public Command {
    public:
    C_dev_map();
    void commence(std::vector<std::string> splitted_input);
};

class C_equip : public Command {
    public:
    C_equip();
    void commence(std::vector<std::string> splitted_input);
};

class C_attack : public Command {
    public:
    C_attack();
    void commence(std::vector<std::string> splitted_input);
};

class C_stock : public Command {
    public:
    C_stock();
    void commence(std::vector<std::string> splitted_input);
};

class C_buy : public Command {
    public:
    C_buy();
    void commence(std::vector<std::string> splitted_input);
};

class C_sell : public Command {
    public:
    C_sell();
    void commence(std::vector<std::string> splitted_input);
};

class C_exit : public Command {
    public:
    C_exit();
    void commence(std::vector<std::string> splitted_input);
};

class C_upgrade : public Command {
    public:
    C_upgrade();
    void commence(std::vector<std::string> splitted_input);
};

class C_scrap : public Command {
    public:
    C_scrap();
    void commence(std::vector<std::string> splitted_input);
};




#endif