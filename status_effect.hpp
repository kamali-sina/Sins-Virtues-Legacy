#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <vector>
#include <string>
#include <iostream>
#include "termcolor.hpp"
#include "dialogs.hpp"

class StatusEffect {
    public:
    StatusEffect();
    virtual void apply();
    virtual void reset();
    std::string getApplyDialog();
    std::string getDescription();
    std::string getString();
    int getTurnsRemaining() { return turns_remaining; }
    std::string getName() { return name; }

    protected:
    int INITIAL_TURNS = 0;
    std::string name = "";
    std::string color = WHITE;
    std::string description = "";
    std::string applyDialog = "";
    int turns_remaining;
};

/*
class StatusEffect:
    def __init__(self):
        self.initial_turns = 0
        self.name = "statuseffect"
        self.color = "magenta"
        # HP change: Has to be - for damage and + for healing
        self.hpc = 0
        self.turns = self.initial_turns
        self.init()
        self.reset()
        if self.hpc > 0:
            self.color = "green"
        elif self.hpc < 0:
            self.color = "red"

    def apply(self, target):
        if self.hpc >= 0:
            target.heal(abs(self.hpc))
        else:
            target.get_damaged(abs(self.hpc))
        self.turns -= 1
        print(self.apply_dialog())

    def apply_dialog(self):
        if self.hpc < 0:
            return f"I got damaged for {self.hpc}hp by the {self.name}"
        elif self.hpc > 0:
            return f"I got healed for {self.hpc}hp by the {self.name}"
        else:
            return f"Still affected by the {self.name}"

    def reset(self):
        self.turns = self.initial_turns

    def init(self):
        self.name = "status"

    def description(self):
        word = ""
        if self.hpc < 0:
            word = "damage"
        elif self.hpc > 0:
            word = "heal"
        else:
            return f"{colored(self.name, self.color)} will affect you for the next {self.turns} turns"
        return f"{colored(self.name, self.color)} will {word} you for {abs(self.hpc)}hp for the next {self.turns} turns"

    def __str__(self):
        return colored(self.name, self.color)
*/

#endif