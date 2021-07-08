#include "dialogs.hpp"

using namespace std;

void introCutscene() {
    cprint("\n======== Sins & Virtues ========", "blue");
    cprint("=== A game made by PapaSinku ===\n", YELLOW);
    dialog("Unknown", "Have you ever been to the SinkuLand?\n", "red", 8);
    dialog("You", "No I can't recall...", YELLOW, 4);
    dialog("Unknown", "Close your eyes, and just imagine SinkuLand...", "red", 10);
    sleep(1);
    cprint("\n> A white light fills the room\n","magenta");
    dialog("You", "Where the hell am I? It's getting dark, better find shelter.", YELLOW, 7);
}

void outOfBoundsDialog() {
    dialog("You", "Ohoh!!! there is a cliff here! I can't move this direction.", YELLOW, 20);
}

void dontHaveItemsDialog() {
    dialog("You", "I do not have that item!", YELLOW, 18);
}

void itemNotInStockDialog() {
    dialog("Shopkeeper", "I do not have that item in stock!", "green", 18);
}

void notEnoughCoinsDialog() {
    dialog("Shopkeeper", "You do not have enough coins to buy that!", "green", 18);
}

void welcomeToShopDialog() {
    dialog("Shopkeeper", "Welcome stranger! Whatever you want, I got it.", "green", 18);
}

void cantUseItemDialog() {
    dialog("You", "I can't use that item!", YELLOW, 17);
}

void cantDigHereDialog() {
    dialog("You", "This is not a digable block!", YELLOW, 17);
}

void foundItemDialog(std::string item_name) {
    dialog("You", "I found a " + item_name + "!", YELLOW, 17);
}

void didntFindItemDialog() {
    dialog("You", "There was nothing here!", YELLOW, 17);
}

void newBlockReachedDialog(std::string block_name, std::string block_info) {
    std::cout<<colored("You",YELLOW) + ": reached a " + block_name + " block. " + block_info<<endl;
}

void deathDialog() {
    dialog("You", "fuck, is this what death is? god damn it hurts...\nI'm just gonna close my eyes for a little bit...\n\ngoodbye...", YELLOW, 6);
}

void defaultKillDialog() {
    dialog("You", "It's over, time to move on...", YELLOW, 17);
}

void cantAttackWithItemDialog() {
    dialog("You", "I can't attack with that item!", YELLOW, 23);
}

void intoTheCastleDialog(int number_of_enemies, std::string boss_name) {
    dialog("You", "Here goes nothing...\nThere are " + std::to_string(number_of_enemies) + " enemies here and a " + boss_name + " boss!", YELLOW, 23);
}

void bossDialog() {
    dialog("You", "Ok time to fight this big bitch!", YELLOW, 23);
}

void noNormalblockPromptDialog() {
    dialog("You", "Yeah I'll play it safe!", YELLOW, 23);
}

void yesNormalblockPromptDialog() {
    dialog("You", "The chest is empty now.", YELLOW, 23);
}

void showPrompt(std::string prompt, std::string block_name, std::string block_color) {
    dialog(block_name, prompt, block_color, 23);
}
