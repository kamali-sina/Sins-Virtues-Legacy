#ifndef _DIALOGS_HP
#define _DIALOGS_HPP

#include <iostream>
#include "console_handler.hpp"

#define PLAYERNAME "You"
#define PLAYERCOLOR YELLOW

void introCutscene();

void loadCutscene();

void outOfBoundsDialog();

void dontHaveItemsDialog();

void itemNotInStockDialog();

void notEnoughCoinsDialog();

void welcomeToShopDialog();

void cantUseItemDialog();

void cantDigHereDialog();

void foundItemDialog(std::string item_name, std::string item_color);

void didntFindItemDialog();

void newBlockReachedDialog(std::string block_name, std::string block_color, std::string block_info);

void deathDialog();

void defaultKillDialog();

void cantAttackWithItemDialog();

void intoTheCastleDialog(int number_of_enemies, std::string boss_name);

void bossDialog();

void noNormalblockPromptDialog();

void yesNormalblockPromptDialog();

void usedSteroidDialog(int new_maxhp);

void itemIsNoLongerUsableDialog(std::string item_name);

void noBlackSmithBlockDialog();

void noShopBlockPromptDialog();

void hpIsNowFullDialog(int hp);

void hpIsNowDialog(int hp);

void noHomeBlockPromptDialog();

void haveToFightEnemyInHomeDialog(std::string enemy_name);

void restAfterFightDialog();

void equippedItemDialog(std::string item_name);

void showPrompt(std::string prompt, std::string block_name, std::string block_color);

void IHaveNoItemsDialog();

void soldItemDialog(int price);

void scrappedDuplicatieItemDialog(std::string item_name, int scrap_amount);

void gotXCoinsDialog(int amount);

void gotXScrapsDialog(int amount);

void welcomeToBlacksmithDialog();

void itemNotScrappableDialog();

void itemNotUpgradbleDialog();

void cantUpgradeMaxitemDialog();

void postUpgradeDialog(std::string item_name, int price, std::string result);

void postScrapDialog(std::string item_name, int price);

void notEnoughScrapsDialog();

void dontWasteMyTimeDialog();

void blockIsClosedDialog(std::string block_name);

void enemyAttacksYouDialog(std::string enemy_name, int damage);

void missedShotDialog();

void understandableHaveAGoodDialog();

void attackedEnemyDialog(std::string enemy_name, int damage);

void newTimeOfDayDialog(int time);

void encounteredEnemyAtNightDialog(std::string enemy_name);

void usedGoldenCarrotDialog();

void noTeleporterBlockDialog();

void yesTeleporterBlockDialog();

void fujilaBoostDialog();

void noCastleBlockDialog();

void fightingCastleEnemyNo(int enemy_number);

void echoBossIntroDialog(std::string boss_name, std::string boss_intro);

void outroCutscene();

#endif