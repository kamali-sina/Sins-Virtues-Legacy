#include "status_effect.hpp"
#include "VnS.hpp"

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


