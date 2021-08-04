#include "dialogs.hpp"

using namespace std;

void introCutscene() {
    cprint("\n======== Sins & Virtues ========", BLUE);
    cprint("=== A game made by PapaSinku ===\n", YELLOW);
    dialog("Unknown", "Have you ever been to the SinkuLand?\n", RED, 8);
    dialog("You", "No I can't recall...", YELLOW, 4);
    dialog("Unknown", "Close your eyes, and just imagine SinkuLand...", RED, 10);
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
    dialog("Shopkeeper", "I do not have that item in stock!", GREEN, 18);
}

void notEnoughCoinsDialog() {
    dialog("Shopkeeper", "You do not have enough coins to buy that! You trying to scam me?", GREEN, 18);
}

void welcomeToShopDialog() {
    dialog("Shopkeeper", "Welcome stranger! Whatever you want, I got it.", GREEN, 18);
}

void understandableHaveAGoodDialog() {
    dialog("Shopkeeper", "Understandable, have a good day!", GREEN, 30);
}

void cantUseItemDialog() {
    dialog("You", "I can't use that item!", YELLOW, 25);
}

void cantDigHereDialog() {
    dialog("You", "This is not a digable block!", YELLOW, 25);
}

void foundItemDialog(std::string item_name) {
    dialog("You", "I got a " + item_name + "!", YELLOW, 25);
}

void didntFindItemDialog() {
    dialog("You", "There was nothing here!", YELLOW, 25);
}

void newBlockReachedDialog(std::string block_name, std::string block_info) {
    std::cout<<colored("You",YELLOW) + ": reached a " + block_name + " block. " + block_info<<endl;
}

void deathDialog() {
    dialog("You", "fuck, is this what death is? god damn it hurts...\nI'm just gonna close my eyes for a little bit...\n\ngoodbye...", YELLOW, 6);
}

void voidaultKillDialog() {
    dialog("You", "It's over, time to move on...", YELLOW, 25);
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

void usedSteroidDialog(int new_maxhp) {
    dialog("You", "max hp is now " + to_string(new_maxhp), YELLOW, 29);
}

void itemIsNoLongerUsableDialog(std::string item_name) {
    dialog("You", item_name + " is no longer usable and I'm dropping it.", YELLOW, 29);
}

void noBlackSmithBlockDialog() {
    dialog("You", "I'll come back when I have more weapon parts!", YELLOW, 29);
}

void noShopBlockPromptDialog() {
    dialog("You", "I'll come back when I have more money.", YELLOW, 29);
}

void noHomeBlockPromptDialog() {
    dialog("You", "Good idea, there might be people in there.", YELLOW, 29);
}

void haveToFightEnemyInHomeDialog(std::string enemy_name) {
    dialog("You", "there is a " + enemy_name + " here, I have to fight it!", YELLOW, 29);
}

void restAfterFightDialog() {
    dialog("You", "I can rest here now...", YELLOW, 29);
}

void equippedItemDialog(std::string item_name) {
    dialog("You", "equipped item is now " + item_name , YELLOW, 29);
}

void IHaveNoItemsDialog() {
    dialog("You", "I have no items in my inventory!" , YELLOW, 29);
}

void hpIsNowFullDialog(int hp) {
    dialog("You", "Hp is now full at " + to_string(hp) + " hp." , YELLOW, 29);
}

void hpIsNowDialog(int hp) {
    dialog("You", "Hp is now at " + to_string(hp) + " hp." , YELLOW, 29);
}


void soldItemDialog(int price) {
    dialog("You", "Sold item for " + to_string(price) + " coins." , YELLOW, 29);
}

void showPrompt(std::string prompt, std::string block_name, std::string block_color) {
    dialog(block_name, prompt, block_color, 23);
}

void scrappedDuplicatieItemDialog(std::string item_name, int scrap_amount) {
    dialog("You", "I already had a " + item_name + " so I scrapped this one for " + to_string(scrap_amount) + " scraps." , YELLOW, 29);
}

void gotXCoinsDialog(int amount) {
    dialog("You", "Found " + to_string(amount) + " coins." , YELLOW, 29);
}

void gotXScrapsDialog(int amount) {
    dialog("You", "Found " + to_string(amount) + " scraps." , YELLOW, 29);    
}

void welcomeToBlacksmithDialog() {
    dialog("Blacksmith", "Welcome stranger! You want stronger weapons? I have it.", BLUE, 22);
}

void itemNotScrappableDialog() {
    dialog("Blacksmith", "I can't scrap that item! it's worthless to me.", BLUE, 27);
}

void itemNotUpgradbleDialog() {
    dialog("Blacksmith", "I can't upgrade that item! it's not an attack item.", BLUE, 28);
}

void cantUpgradeMaxitemDialog() {
    dialog("Blacksmith", "I can't upgrade that item anymore! it's at max level.", BLUE, 22);
}

void notEnoughScrapsDialog() {
    dialog("Blacksmith", "You do not have enough scraps to upgrade that!", BLUE, 24);
}

void dontWasteMyTimeDialog() {
    dialog("Blacksmith", "Don't waste my time. either upgrade or get out!", BLUE, 30);
}

void postUpgradeDialog(std::string item_name, int price, std::string result) {
    dialog("Blacksmith", "upgraded " + item_name + " for " + to_string(price) + " parts. " + result, BLUE, 30);
}

void postScrapDialog(std::string item_name, int price) {
    dialog("Blacksmith", "scrapped " + item_name + " for " + to_string(price) + " scraps.", BLUE, 30);
}