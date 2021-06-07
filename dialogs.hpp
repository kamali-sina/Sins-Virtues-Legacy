#ifndef _DIALOGS_HP
#define _DIALOGS_HPP

#include <iostream>
#include "console_handler.hpp"

void intro_cutscene();

void out_of_bounds_dialog();

void dont_have_items_dialog();

void item_not_in_stock_dialog();

void not_enough_coins_dialog();

void welcome_to_shop_dialog();

void cant_use_item_dialog();

void cant_dig_here_dialog();

void found_item_dialog(std::string item_name);

void didnt_find_item_dialog();

void new_block_reached_dialog(std::string block_name, std::string block_info);

void death_dialog();

void default_kill_dialog();

void cant_attack_with_item_dialog();

void into_the_castle_dialog(int number_of_enemies, std::string boss_name);

void boss_dialog();

#endif