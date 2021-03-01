#ifndef _DIALOGS_HP
#define _DIALOGS_HPP

#include <iostream>
#include "console_handler.hpp"

void intro_cutscene(){
    cprint("\n======== Sins & Virtues ========", "blue");
    cprint("=== A game made by PapaSinku ===\n", YELLOW);
    dialog("Unknown", "Have you ever been to the SinkuLand?\n", "red", 8);
    dialog("You", "No I can't recall...", YELLOW, 4);
    dialog("Unknown", "Close your eyes, and just imagine SinkuLand...", "red", 10);
    sleep(1);
    cprint("\n> A white light fills the room\n","magenta");
    sleep(0.5);
    dialog("You", "Where the hell am I? It's getting dark, better find shelter.", YELLOW, 7);
}

void out_of_bounds_dialog(){
    dialog("You", "Ohoh!!! there is a cliff here! I can't move this direction.", YELLOW, 20);
}

void dont_have_items_dialog(){
    dialog("You", "I do not have that item!", YELLOW, 18);
}

void item_not_in_stock_dialog(){
    dialog("Shopkeeper", "I do not have that item in stock!", "green", 18);
}

void not_enough_coins_dialog(){
    dialog("Shopkeeper", "You do not have enough coins to buy that!", "green", 18);
}

void welcome_to_shop_dialog(){
    dialog("Shopkeeper", "Welcome stranger! Whatever you want, I got it.", "green", 18);
}

void cant_use_item_dialog(){
    dialog("You", "I can't use that item!", YELLOW, 17);
}

void cant_dig_here_dialog(){
    dialog("You", "This is not a digable block!", YELLOW, 17);
}

void found_item_dialog(std::string item_name){
    dialog("You", "I found a " + item_name + "!", YELLOW, 17);
}

void didnt_find_item_dialog(){
    dialog("You", "There was nothing here!", YELLOW, 17);
}

void new_block_reached_dialog(std::string block_name, std::string block_info){
    std::cout<<colored("You",YELLOW) + ": reached a " + block_name + " block. " + block_info;
}

void death_dialog(){
    dialog("You", "fuck, is this what death is? god damn it hurts...\nI'm just gonna close my eyes for a little bit...\n\ngoodbye...", YELLOW, 6);
}

void default_kill_dialog(){
    dialog("You", "It's over, time to move on...", YELLOW, 17);
}

void cant_attack_with_item_dialog(){
    dialog("You", "I can't attack with that item!", YELLOW, 23);
}

void into_the_castle_dialog(int number_of_enemies, std::string boss_name){
    dialog("You", "Here goes nothing...\nThere are " + std::to_string(number_of_enemies) + " enemies here and a " + boss_name + " boss!", YELLOW, 23);
}

void boss_dialog(){
    dialog("You", "Ok time to fight this big bitch!", YELLOW, 23);
}

#endif