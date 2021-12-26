#include "status_effect.hpp"
#include "VnS.hpp"

using namespace std;

/* ==================== Base Status Effect ==================== */

StatusEffect::StatusEffect()  { 
    reset();
}

std::string StatusEffect::getDescription() {
    return description;
}

std::string StatusEffect::getApplyDialog() {
    return applyDialog;
}

std::string StatusEffect::getString() {
    return colored(name, color);
}

void StatusEffect::reset() {
    turns_remaining = INITIAL_TURNS;
}

bool StatusEffect::tagsContain(std::string tag) {
    for (int i = 0 ; i < tags.size() ; i++) {
        if (tags[i] == tag) return true;
    }
    return false;
}

void StatusEffect::apply() {
    _error("base apply was called!");
}

/* ==================== DPS Status Effect Base ==================== */

DPSEffect::DPSEffect() {
    INITIAL_TURNS = 0;
    hp_change = 0;
    name = "dps";
    tags.push_back(DPSTAG);
    color = WHITE;
    description = "";
    applyDialog = "";
    reset();
}

void DPSEffect::apply() {
    if (hp_change > 0) {
        notification(name + "is " + colored("healing", GREEN) + " you...");
        session.getPlayer()->heal(hp_change);
    } else {
        notification(name + "is " + colored("damaging", RED) + " you...");
        session.getPlayer()->getDamaged(-1 * hp_change);
    }
    turns_remaining -= 1;
}

std::string DPSEffect::getApplyDialog() {
    string mode = "";
    if (hp_change > 0) {
        mode = "heal";
    } else {
        mode = "damage";
    }
    return this->getString() + " will " + mode + " you for the next " + to_string(INITIAL_TURNS) + " turn(s)!";
}

/* ==================== Poison ==================== */

Poison::Poison() {
    INITIAL_TURNS = 3;
    hp_change = -2;
    name = "poison";
    color = GREEN;
    description = "A slow poison that will damage you for " + to_string(hp_change) + "hp each turn";
    applyDialog = "";
    reset();
}