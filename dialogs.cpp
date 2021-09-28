#include "dialogs.hpp"

using namespace std;

void introCutscene() {
    cprint("\n======== Sins & Virtues ========", BLUE);
    cprint("=== A game made by PapaSinku ===\n", YELLOW);
    dialog("Unknown", "Have you ever been to the SinkuLand?\n", RED, 14);
    dialog("You", "No I can't recall...", YELLOW, 12);
    dialog("Unknown", "Close your eyes, and just imagine SinkuLand...", RED, 15);
    sleep(1);
    cprint("\n> A white light fills the room\n", MAGENTA);
    dialog("You", "Where the hell am I? It's getting dark, better find shelter.", YELLOW, 20);
}

void outroCutscene() {
    dialog("You", " *panting* holy shit it's over... what's that over there?", YELLOW, 15);
    sleep(1);
    dialog("You", "what the hell? is that... me? hey you ok man?", YELLOW, 15);
    notification("*you try to wake yourself up*");
    sleep(1);
    cprint("\n> A white light fills the room\n", MAGENTA);
    sleep(1);
    dialog("Unknown", "Open your eyes, do you know where you just went?", RED, 15);
    dialog("You", "*trying to open eyes* what? no. where am I?", YELLOW, 15);
    dialog("Unknown", "You are back in your room. The simulation is over.", RED, 15);
    dialog("You", "Is this real? was that real? what just happened?", YELLOW, 15);
    dialog("Unknown", "A thought that shapes in your head has found meaning. No one knows where is SinkuLand and what are the creatures that live there, but each time you go inside, we learn a bit more! We'll be waiting for you on the other side.", RED, 15);
    dialog("You", "*you turn off the computer*", YELLOW, 15);
    notification("\nThe End\n");
}

void loadCutscene() {
    cprint("\n======== Sins & Virtues ========", BLUE);
    cprint("=== A game made by PapaSinku ===\n", YELLOW);
    dialog("You", "Where am I? Why do I feel so disconnected from myself?", YELLOW, 20);
    dialog("You", "Oh shit, It's morning already? I have to get going!", YELLOW, 20);
}

void outOfBoundsDialog() {
    dialog("You", "Ohoh!!! there is a cliff here! I can't move this direction.", YELLOW, 20);
}

void dontHaveItemsDialog() {
    dialog("You", "I do not have that item!", YELLOW, 18);
}

void cantSellThatItemDialog() {
    dialog("You", "I can not sell that item! I might need it later.", YELLOW, 25);
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

void foundItemDialog(std::string item_name, std::string item_color) {
    dialog("You", "I got a " + colored(item_name, item_color) + "!", YELLOW, 25);
}

void didntFindItemDialog() {
    dialog("You", "There was nothing here!", YELLOW, 25);
}

void newBlockReachedDialog(std::string block_name, std::string block_color, std::string block_info) {
    std::cout<<colored("You",YELLOW) + ": reached a " + colored(block_name, block_color) + " block. " + block_info<<endl;
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
    dialog("You", "Here goes nothing...\nThere are " + std::to_string(number_of_enemies) 
            + " enemies here and a " + colored(boss_name, RED)  + " boss!", YELLOW, 23);
}

void bossDialog() {
    dialog("You", "Ok... that's all the goons! Time to fight the big bad bitch!", YELLOW, 23);
}

void noNormalblockPromptDialog() {
    dialog("You", "Yeah I'll play it safe!", YELLOW, 23);
}

void yesNormalblockPromptDialog() {
    dialog("You", "The chest is empty now.", YELLOW, 23);
}

void usedSteroidDialog(int new_maxhp) {
    dialog("You", "I feel way tougher now! max hp is now " + colored(to_string(new_maxhp), GREEN), YELLOW, 29);
}

void usedGoldenCarrotDialog() {
    dialog("You", "Wow that was delicious! I can see way better now! map vision upgraded.", YELLOW, 29);
}

void itemIsNoLongerUsableDialog(std::string item_name) {
    dialog("You", colored(item_name, BLUE) + " is no longer usable and I'm dropping it.", YELLOW, 29);
}

void noBlackSmithBlockDialog() {
    dialog("You", "I'll come back when I have more weapon parts!", YELLOW, 29);
}

void noTeleporterBlockDialog() {
    dialog("You", "Yea I better not use every weired thing in this woods!", YELLOW, 29);
}

void yesTeleporterBlockDialog() {
    dialog("You", "Ok here goes nothing! where to?", YELLOW, 29);
}

void noShopBlockPromptDialog() {
    dialog("You", "I'll come back when I have more money.", YELLOW, 29);
}

void noHomeBlockPromptDialog() {
    dialog("You", "Good idea, there might be people in there.", YELLOW, 29);
}

void haveToFightEnemyInHomeDialog(std::string enemy_name) {
    dialog("You", "there is a " + colored(enemy_name, RED) + " here, I have to fight it!", YELLOW, 29);
}

void restAfterFightDialog() {
    dialog("You", "I can rest here now...", YELLOW, 29);
}

void equippedItemDialog(std::string item_name) {
    dialog("You", "equipped item is now " + colored(item_name, RED), YELLOW, 29);
}

void IHaveNoItemsDialog() {
    dialog("You", "I have no items in my inventory!" , YELLOW, 29);
}

void hpIsNowFullDialog(int hp) {
    dialog("You", "Hp is now full at " + colored(to_string(hp), RED) + " hp." , YELLOW, 29);
}

void hpIsNowDialog(int hp) {
    dialog("You", "Hp is now at " + colored(to_string(hp), RED) + " hp." , YELLOW, 29);
}


void soldItemDialog(int price) {
    dialog("You", "Sold item for " + colored(to_string(price), YELLOW) + " coins." , YELLOW, 29);
}

void showPrompt(std::string prompt, std::string block_name, std::string block_color) {
    dialog(block_name, prompt, block_color, 23);
}

void scrappedDuplicatieItemDialog(std::string item_name, int scrap_amount) {
    dialog("You", "I already had a " + colored(item_name, RED) 
            + " so I scrapped this one for " + colored(to_string(scrap_amount), BLACK) + " scraps." , YELLOW, 29);
}

void gotXCoinsDialog(int amount) {
    dialog("You", "Found " + colored(to_string(amount), YELLOW) + " coins." , YELLOW, 29);
}

void gotXScrapsDialog(int amount) {
    dialog("You", "Found " + colored(to_string(amount), BLACK) + " scraps." , YELLOW, 29);    
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
    dialog("Blacksmith", "upgraded " + colored(item_name, RED) 
            + " for " + colored(to_string(price), BLACK) + " parts. " + result, BLUE, 30);
}

void postScrapDialog(std::string item_name, int price) {
    dialog("Blacksmith", "scrapped " + colored(item_name, RED) + " for " + colored(to_string(price), BLACK) + " scraps.", BLUE, 30);
}

void blockIsClosedDialog(std::string block_name) {
    dialog("You", "The " + block_name + " is closed at nights, better find another shelter.", YELLOW, 26);
}

void enemyAttacksYouDialog(std::string enemy_name, int damage) {
    notification(colored(enemy_name, RED) + " attacks you for " + colored(to_string(damage), RED) + " damage!");
}

void missedShotDialog() {
    dialog("You", "Oh shit I missed!!!", YELLOW, 26);
}

void attackedEnemyDialog(std::string enemy_name, int damage) {
    notification("Attacked the " + colored(enemy_name, RED) 
            + " for " + colored(to_string(damage), RED) + " damage!!!");
}

void newTimeOfDayDialog(int time) {
    string message = "";
    if (time == 0)
        message = "The sun is rising! I was up all night god damn. Can't stop now...";
    else if (time == 1)
        message = "It's dusk, getting dark soon, better find shelter fast.";
    else
        message = "It's night. Shops are closed. The night is dark and full of terrors...";
    dialog("You", message, YELLOW, 22);
}

void encounteredEnemyAtNightDialog(std::string enemy_name) {
    dialog("You", "Shit there is a " + colored(enemy_name, RED) 
            + " here, Shit! Can't escape, have to fight it!", YELLOW, 30);
}

void fujilaBoostDialog() {
    dialog("You", "Holy shit, the " + colored("Fujila", RED) 
            + " is boosting itself! It now has increased speed and damage!!!", YELLOW, 30);
}

void noCastleBlockDialog() {
    dialog("You", "Oh thank god! This place looks scary af!", YELLOW, 30);
}

void fightingCastleEnemyNo(int enemy_number) {
    if (enemy_number == 1) {
        dialog("You", "Last one, one more and I'm free!", YELLOW, 30);
        return;
    }
    dialog("You", "Here we go, goon number " + to_string(enemy_number) + "!", YELLOW, 30);
}

void echoBossIntroDialog(std::string boss_name, std::string boss_intro) {
    dialog(boss_name, boss_intro, BOLDRED, 30);
}