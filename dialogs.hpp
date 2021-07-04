#ifndef _DIALOGS_HP
#define _DIALOGS_HPP

#include <iostream>
#include "console_handler.hpp"

void introCutscene();

void outOfBoundsDialog();

void dontHaveItemsDialog();

void itemNotInStockDialog();

void notEnoughCoinsDialog();

void welcomeToShopDialog();

void cantUseItemDialog();

void cantDigHereDialog();

void foundItemDialog(std::string item_name);

void didntFindItemDialog();

void newBlockReachedDialog(std::string block_name, std::string block_info);

void deathDialog();

void defaultKillDialog();

void cantAttackWithItemDialog();

void intoTheCastleDialog(int number_of_enemies, std::string boss_name);

void bossDialog();

void noNormalblockPromptDialog();

void yesNormalblockPromptDialog();

#endif