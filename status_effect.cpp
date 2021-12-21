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

void StatusEffect::apply() {
    _error("base apply was called!");
}

/* ==================== DPS Status Effect Base ==================== */

DPSEffect::DPSEffect() {
    INITIAL_TURNS = 0;
    hp_change = 0;
    name = "dps";
    color = WHITE;
    description = "";
    applyDialog = "";
    reset();
}

void DPSEffect::apply() {
    if (hp_change > 0) {
        session.getPlayer()->heal(hp_change);
    } else {
        session.getPlayer()->getDamaged(-1 * hp_change);
    }
    turns_remaining -= 0;
}

std::string DPSEffect::getApplyDialog() {
    string mode = "";
    if (hp_change > 0) {
        mode = "heal";
    } else {
        mode = "damage";
    }
    return this->getString() + " will " + mode + " you for the next " + to_string(turns_remaining) + " turn(s)!";
}

/* ==================== Poison ==================== */

Poison::Poison() {
    INITIAL_TURNS = 3;
    hp_change = -2;
    name = "poison";
    color = GREEN;
    description = "A slow poison that will damage you each turn";
    applyDialog = "";
    reset();
}