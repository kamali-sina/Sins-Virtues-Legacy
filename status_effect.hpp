#ifndef _STATUS_EFFECT_HPP
#define _STATUS_EFFECT_HPP

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
    virtual std::string getApplyDialog();
    virtual std::string getDescription();
    virtual std::string getString();
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

class DPSEffect : public StatusEffect {
    public:
    DPSEffect();
    void apply();
    std::string getApplyDialog();

    protected:
    int hp_change = 0;
};

class Poison : public DPSEffect {
    public:
    Poison();
};

#endif